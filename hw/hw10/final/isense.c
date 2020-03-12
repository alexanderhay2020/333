#include "NU32.h"
#include <stdio.h>
#include "isense.h"


void ADC_init(void) {
  AD1PCFGbits.PCFG0 = 0;                 // AN0 is an adc pin
  AD1CON3bits.ADCS = 2;                   // ADC clock period is Tad = m2*(ADCS+1)*Tpb = 2*3*12.5ns = 75ns
  AD1CON1bits.ADON = 1;
}


unsigned int adc_sample_convert(int pin) { // sample & convert the value on the given
  unsigned int elapsed_time = 0;
  unsigned int finish_time = 0;
  AD1CHSbits.CH0SA = pin;                // connect chosen pin to MUXA for sampling
  AD1CON1bits.SAMP = 1;                  // start sampling
  elapsed_time = _CP0_GET_COUNT();
  finish_time = elapsed_time + 10;
  while (_CP0_GET_COUNT() < finish_time) {
    ;                                   // sample for more than 250 ns
  }
  AD1CON1bits.SAMP = 0;                 // stop sampling and start converting
  while (!AD1CON1bits.DONE) {
    ;                                   // wait for the conversion process to finish
  }
  return ADC1BUF0;                      // read the buffer with the result
}

// Loop doesn't work
// unsigned int read_adc(){
//   int i = 0;
//   int sum = 0;
//   for (i=0; i++; i<10){
//     sum = sum + adc_sample_convert(0);
//   }
//   return (sum/10);
// }


unsigned int read_adc() {
  int i = 0;
  int sum = 0;
  while (i<=10) {
    sum += adc_sample_convert(0);
    i++;
  }
  return (sum/10);
}


int current(void) {
  return (6.26*read_adc() - 3501);
}
