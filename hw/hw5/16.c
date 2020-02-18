#include "NU32.h"                     // constants, funcs for startup and UART
#define DELAYTIME 400000              // 400 thousand core clock ticks, or 0.01 second


void debounce(){
  _CP0_SET_COUNT(0);
  while(_CP0_GET_COUNT() < DELAYTIME) {
    ;
  }
}


void __ISR(_EXTERNAL_0_VECTOR, IPL2SOFT) Ext0ISR(void) { // step 1: the ISR
  _CP0_SET_COUNT(0);
  debounce();                       // (wait 10ms)
  if (PORTDbits.RD0 == 0){
    NU32_LED1 = 1;                    // LED1 and LED2 off
    NU32_LED2 = 1;
  }
  IFS0bits.INT0IF = 0;              // clear interrupt flag IFS0<3>
}


int main(void) {
  NU32_Startup();                     // cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 0;                      // LED1 and LED2 on
  NU32_LED2 = 0;
  __builtin_disable_interrupts();     // step 2: disable interrupts
  INTCONbits.INT0EP = 0;              // step 3: INT0 triggers on falling edge
  IPC0bits.INT0IP = 2;                // step 4: interrupt priority 2
  IPC0bits.INT0IS = 1;                // step 4: interrupt priority 1
  IFS0bits.INT0IF = 0;                // step 5: clear the int flag
  IEC0bits.INT0IE = 1;                // step 6: enable INT0 by setting IEC0<3>
  __builtin_enable_interrupts();      // step 7: enable interrupts
                                      // Connect RD7 (USER button) to INT0 (D0)

  find RD7 on processor diagram. pin d0 has an int, RD7 does not, so D0 = INT0


  while(1) {
    ; // do nothing, loop forever
  }

  return 0;
}
