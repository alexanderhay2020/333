#include "NU32.h"

#define NUMSAMPS 1000             // number of points in a waveform
static volatile int Waveform[NUMSAMPS]; // waveform


void makeWaveform(){

  int i = 0;
  int center = 2000;                     // Center based on PR3 (1/2 PR3)
  int A = 1000;                          // Amplitude (3) 25% of PR3

  for (i=0; i<NUMSAMPS; i++){
    if (i<NUMSAMPS/2){
      Waveform[i] = center + A;
    }
    else{
      Waveform[i] = center - A;
    }
  }
}


void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) { // _TIMER_2_VECTOR = 8

  static int counter = 0;         // initialize counter once
  OC1RS = Waveform[counter];      // duty cycle = OC1RS/(PR2+1) = 25%
  counter++;                      // add one to counter every time ISR is entered

  if (counter == NUMSAMPS) {
    counter = 0;                  // roll the counter over when needed
  }
  IFS0CLR = 0x1000;               // clear interrupt flag IFS0
}


int main(void){

  NU32_Startup();                 // cache on, interrupts on, LED/button init, UART init

  TRISDbits.TRISD0 = 0;           // make D1 an output

  makeWaveform();

  T3CONbits.TCKPS = 0;            // Timer3 prescaler N=1
  PR3 = 3999;                     // period = (PR3+1) * N * 12.5 ns = 50us. 20kHz
  TMR3 = 0;                       // initial TMR3 count is 0
  OC1CONbits.OCTSEL = 1;          // selects Timer3
  OC1CONbits.OCM = 0b110;         // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = 3000;                   // duty cycle = OC1RS/(PR2+1) = 25%
  OC1R = 3000;                    // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;               // turn on Timer3
  OC1CONbits.ON = 1;              // turn on OC1

  __builtin_disable_interrupts(); // step 2: disable interrupts
  INTCONbits.INT0EP = 0;          // step 3: INT0 triggers on falling edge
  // IPC3bits.T3IP = 5;              // step 4: interrupt priority 5
  IFS0bits.INT0IF = 0;            // step 5: clear the int flag
  IEC0bits.INT0IE = 1;            // step 6: enable INT0 by setting IEC0<3>
  __builtin_enable_interrupts();  // step 7: enable interrupts

  while(1){
    ;
  }
  return 0;
}
