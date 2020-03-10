#include <xc.h>
#include "NU32.h"

void ADC_init(void){
  AD1PCFGbits.PCFG0 = 0;                  // AN0 is an adc pin
  AD1CON3bits.ADCS = 2;                   // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
                                          //                           2*3*12.5ns = 75ns
  AD1CON1bits.ADON = 1;
}


unsigned int adc_sample_convert(int pin) {
	unsigned int elapsed = 0;
	unsigned int finish_time = 0;
  AD1CON1 = 0x80E6;
	AD1CHSbits.CH0SA = pin;		                  // connect chosen pin to MUXA for sampling
	elapsed = _CP0_GET_COUNT();
	finish_time = elapsed + 100;	              // 10 core timer ticks = 250 ns
	while (_CP0_GET_COUNT() < finish_time) {
		;				                                  // sample for more than 250 ns
	}
  while (!AD1CON1bits.DONE) {
    ;                                         // wait for the conversion process to finish
  }
	return ADC1BUF0;		                  	    // read the buffer with the result
}


unsigned int read_adc(){
  int i = 0;
  int sum = 0;
  for (i; i++; i<10){
    sum += adc_sample_convert(0);
  }
  return sum/10;
}
