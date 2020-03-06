#include "NU32.h"
#include <stdio.h>

#define NUMSAMPS 1000             // number of points in a waveform
#define PLOTPTS 200               // number of data points to plot
#define DECIMATION 10             // plot every 10th point
#define SAMPLE_TIME 10

static volatile int Waveform[NUMSAMPS]; // waveform
static volatile int ADCarray[PLOTPTS];  // measured values to plot
static volatile int REFarray[PLOTPTS];  // reference values to plot
static volatile int StoringData = 0;    // if this flag = 1, currently storing plot data
static volatile float Kp = 0, Ki = 0;   // control gains
static volatile int eint = 0;


int hits = 0;

void makeWaveform(){

  int i = 0;
  int center = 500;                     // Center based on PR3 (1/2 PR3)
  int A = 300;                          // Amplitude (3) 25% of PR3

  for (i=0; i<NUMSAMPS; i++){
    if (i<NUMSAMPS/2){
      Waveform[i] = center + A;
    }
    else{
      Waveform[i] = center - A;
    }
  }
}


unsigned int adc_sample_convert(int pin) {	// sample & convert the value
  								                          // on the given adc pin the pin
                                            // should be configured as an
                                            // analog input in AD1PCFG
	unsigned int elapsed = 0;
	unsigned int finish_time = 0;
  // AD1CON1bits.ON = 1;                    // bit 15 sets it ON
  // AD1CON1bits.SSRC = 0b111;              // bits 7:5 enable end sampling & starts conversion
  // AD1CON1bits.ASAM = 1;                  // bit 2 has ADC sample audio start bit
  // AD1CON1bits.SAMP = 1;                  //start sampling
  AD1CON1 = 0x80E6;
	AD1CHSbits.CH0SA = pin;		                // connect chosen pin to MUXA for
						                                // sampling
	elapsed = _CP0_GET_COUNT();
	finish_time = elapsed + 100;	              // 10 core timer ticks = 250 ns
	while (_CP0_GET_COUNT() < finish_time) {
		;				                                // sample for more than 250 ns
	}
  while (!AD1CON1bits.DONE) {
    ;                                       // wait for the conversion process to finish
  }
	return ADC1BUF0;		                  	  // read the buffer with the result
}


void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) { // _TIMER_2_VECTOR = 8

  static int counter = 0;         // initialize counter once
  static int plotind = 0;         // index for data arrays; counts up to PLOTPTS
  static int decctr = 0;          // counts to store data one every DECIMATION
  static int adcval = 0;
  float unew = 0;
  float u = 0, e = 0;

  //  OC1RS = Waveform[counter];      // duty cycle = OC1RS/(PR2+1) = 25%

  // read ADC value into ISR, using adcval
  adcval = adc_sample_convert(0);
  e = Waveform[counter] - adcval;
  eint = eint + e;
  u = (Kp*e) + (Ki*eint);
  unew = u + 50.0;
  if (unew > 100.0) {
    unew = 100.0;
  }
  else if (unew < 0.0) {
    unew = 0.0;
  }

  OC1RS = (unsigned int) ((unew/100.0) * PR3);

  if (StoringData) {
    decctr++;

    if (decctr == DECIMATION) {     // after DECIMATION control loops,
      decctr = 0;                   // reset decimation counter
      ADCarray[plotind] = adcval;   // store data in global arrays
      REFarray[plotind] = Waveform[counter];
      plotind++;                    // increment plot data index
    }

    if (plotind == PLOTPTS) {       // if max number of plot points plot is reached,
      plotind = 0;                  // reset the plot index
      StoringData = 0;              // tell main data is ready to be sent to MATLAB
    }
  }

  counter++;                      // add one to counter every time ISR is entered
  if (counter == NUMSAMPS) {
    counter = 0;                  // roll the counter over when needed
  }

  IFS0bits.T2IF = 0;              // clear interrupt flag IFS0
}


int main(void){

  char message[100];              // message to and from MATLAB
  float kptemp = 0;               // temporary Kp gain
  float kitemp = 0;               // temporary Ki gain
  int i = 0;                      // plot data loop index
  // float eint = 0;

  NU32_Startup();                 // cache on, interrupts on, LED/button init, UART init
  makeWaveform();

  AD1CON3bits.ADCS = 2;
  // AD1CON1bits.ADON = 1;
  T3CONbits.TCKPS = 0;            // Timer3 prescaler N=1
  PR3 = 3999;                     // period = (PR3+1) * N * 12.5 ns = 50us. 20kHz
  TMR3 = 0;                       // initial TMR3 count is 0
  OC1CONbits.OCTSEL = 1;          // selects Timer3
  OC1CONbits.OCM = 0b110;         // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = 3000;                   // duty cycle = OC1RS/(PR2+1) = 75%
  OC1R = 3000;                    // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;               // turn on Timer3
  OC1CONbits.ON = 1;              // turn on OC1

  __builtin_disable_interrupts(); // step 2: disable interrupts

  T2CONbits.TCKPS = 1;
  PR2 = 39999;
  TMR2 = 0;
  T2CONbits.ON = 1;
  IPC2bits.T2IP = 5;              // step 4: interrupt priority 5
  IFS0bits.T2IF = 0;              // step 5: clear the int flag
  IEC0bits.T2IE = 1;              // step 6: enable INT0 by setting IEC0<3>

  __builtin_enable_interrupts();  // step 7: enable interrupts

  while(1){

    NU32_ReadUART3(message, sizeof(message));     // wait for message from MATLAB
    sscanf(message, "%f %f" , &kptemp, &kitemp);
    __builtin_disable_interrupts(); // keep ISR disabled as briefly as possible
    Kp = kptemp;                    // copy local variables to globals used by ISR
    Ki = kitemp;
    eint = 0;
    __builtin_enable_interrupts();  // only 2 simple C commands while ISRs disabled
    StoringData = 1;                // message to ISR to start storing data

    while (StoringData) {           // wait until ISR says data storing is done
      ;                             // do nothing
    }

    for (i=0; i<PLOTPTS; i++) {     // send plot data to MATLAB
                                    // when first number sent = 1, MATLAB knows we’re done
      sprintf(message, "%d %d %d\r\n", PLOTPTS-i, ADCarray[i], REFarray[i]);
      NU32_WriteUART3(message);
    }
  }

  return 0;
}
