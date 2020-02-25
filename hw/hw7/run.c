#include "NU32.h"

#define NUMSAMPS 1000             // number of points in a waveform
static volatile int Waveform[NUMSAMPS]; // waveform


void makeWaveform(){
  int i = 0;
  center = ?;                     // Center
  A = ?;                          // Amplitude

  for (i=0; i<NUMSAMPS; i++){
    if (i<NUMSAMPS/2){
      Waveform[i] = center + A;
    }
    else{
      Waveform[i] = center - A;
    }
  }
}


int main(void){
  NU32_Startup();                 // cache on, interrupts on, LED/button init, UART init

  TRISDbits.TRISD0 = 0;           // make D1 an output

  T3CONbits.TCKPS = 0;            // Timer3 prescaler N=1
  PR3 = 3999;                     // period = (PR3+1) * N * 12.5 ns = 50us. 20kHz
  TMR3 = 0;                       // initial TMR3 count is 0
  OC1CONbits.OCTSEL = 1;          // selects Timer3
  OC1CONbits.OCM = 0b110;         // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = 3000;                   // duty cycle = OC1RS/(PR2+1) = 25%
  OC1R = 3000;                    // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;               // turn on Timer3
  OC1CONbits.ON = 1;              // turn on OC1

  while(1){
    ;
  }
  return 0;
}
