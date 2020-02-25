#include "NU32.h"

unsigned int adc_sample_convert(int pin) {	// sample & convert the value
  								                          // on the given adc pin the pin
                                            // should be configured as an
                                            // analog input in AD1PCFG
	unsigned int elapsed = 0,
	finish_time = 0;
	AD1CHSbits.CH0SA = pin;		                // connect chosen pin to MUXA for
						                                // sampling
	elapsed = _CP0_GET_COUNT();
	finish_time = elapsed + 10;	              // 10 core timer ticks = 250 ns
	while (_CP0_GET_COUNT() < finish_time) {
		;				                                // sample for more than 250 ns
	}
	return ADC1BUF0;		                  	  // read the buffer with the result
}


void main(void){}
