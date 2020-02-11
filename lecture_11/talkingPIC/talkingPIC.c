#include "NU32.h"          // constants, funcs for startup and UART

#define MAX_MESSAGE_LENGTH 200

int main(void) {
  char message[MAX_MESSAGE_LENGTH];

  int i;

  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    sscanf(message, "%d", &i);
    if(i == 33){
      NU32_WriteUART3("ye");
    }
    else{
      NU32_WriteUART3("no");
    }
    // NU32_WriteUART3(message);                     // send message back
    NU32_WriteUART3("\r\n");                      // carriage return and newline
    LATF = 0;                                     // turn all pins off
    NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
    NU32_LED2 = !NU32_LED2;
  }
  return 0;
}
