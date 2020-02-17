#include "NU32.h"

void __ISR(_EXTERNAL_0_VECTOR, IPL2SFOT) Ex0ISR(void){
  NU32_LED1 = 0;
  NU32_LED2 = 0;
  _CP0_SET_COUNT(0);

  while(_CP0_GET_COUNT() < 10000000) { ; }    // delay forr 10M core cycles

  NU32_LED1 = 1;                      // LED1 qne LED2 are on
  NU32_LED2 = 1;
  IFS0bits.INT0IF = 0;
}

int main(void){
  NU32_startup();
  __builtin_disable_interrupts();     // disable interrupts
  INTCONbits.INT0EP = 0;              // INT0 triggers on false
  IPC0bits.INT0IP = 2;                // interrupt priority 2
  IPC0bits.INT0IS = 1;                // interrupt priority 1
  IFS0bits.INT0IF = 0;                // clear int flag
  IEC0bits.INT0IE = 1;                // enable INT0 by setting
  __builtin_enable_interrupts();      // enable interrupts
}


Debounce:

  ISR(){
    delay(5);
    read button
    if low //pressed
      do whatever
    else()
  }
