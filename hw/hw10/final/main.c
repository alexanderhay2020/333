#include <xc.h>
#include <stdio.h>
#include "NU32.h"                           // config bits, constants, funcs for startup and UART
#include "encoder.h"
#include "isense.h"

#define BUF_SIZE 200

int main() {
  char buffer[BUF_SIZE];
  NU32_Startup();                           // cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;                            // turn off the LEDs
  NU32_LED2 = 1;

  __builtin_disable_interrupts();
  encoder_init();
  ADC_init();
  __builtin_enable_interrupts();

  while(1) {
    NU32_ReadUART3(buffer,BUF_SIZE);        // we expect the next character to be a menu command
    NU32_LED2 = 1;                          // clear the error LED
    switch (buffer[0]) {

      case 'a': {                           // read encoder counts
        sprintf(buffer,"%d", read_adc());
        NU32_WriteUART3(buffer);            // send encoder count to client
        break;
      }

      case 'c': {                           // read encoder counts
        sprintf(buffer, "%d\r\n", encoder_counts());  // encoder_counts is in encoder.c
        NU32_WriteUART3(buffer);            // send encoder count to client
        break;
      }

      case 'd': {                           // read encoder degrees
        sprintf(buffer, "%d\r\n", degree());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'e': {                           // read encoder degrees
        sprintf(buffer, "%d\r\n", encoder_reset());  // encoder_counts is in encoder.c
        NU32_WriteUART3(buffer);
        break;
      }

      case 'n': {                           // dummy command for demonstration purposes
        int n = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n);
        sprintf(buffer,"%d\r\n", n + 1);    // return the number + 1
        NU32_WriteUART3(buffer);
        break;
      }

      case 'q': {
        // handle q for quit. Later you may want to return to IDLE mode here.
        break;
      }

      case 'x': {                           // test command
        int a = 0;
        int b = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &a);
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &b);
        sprintf(buffer,"%d\r\n", (a + b));
        NU32_WriteUART3(buffer);
      }

      default: {
        NU32_LED2 = 0;                      // turn on LED2 to indicate an error
        break;
      }
    }
  }
  return 0;
}
