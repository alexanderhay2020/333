#include <xc.h>
#include <stdio.h>
#include "NU32.h"                           // config bits, constants, funcs for startup and UART
#include "utilities.h"
#include "encoder.h"
#include "isense.h"
#include "currentcontrol.h"

#define BUF_SIZE 20

int main() {

  char buffer[BUF_SIZE];
  extern volatile modes MODE;
  extern volatile int duty_cycle;
  extern volatile int kI;


  NU32_Startup();                           // cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;                            // turn off the LEDs
  NU32_LED2 = 1;


  __builtin_disable_interrupts();

  encoder_init();
  ADC_init();
  PWM_init();

  MODE = IDLE;
  __builtin_enable_interrupts();


  while(1) {
    NU32_ReadUART3(buffer,BUF_SIZE);        // we expect the next character to be a menu command
    NU32_LED2 = 1;                          // clear the error LED
    switch (buffer[0]) {

      case 'a': {                           // read current counts
        sprintf(buffer,"%d\r\n", read_adc());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'b': {                           // read current mA
        sprintf(buffer,"%d\r\n", current());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'c': {                           // read encoder counts
        int blah = encoder_counts();
        sprintf(buffer, "%d\r\n", encoder_counts());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'd': {                           // read encoder degrees
        sprintf(buffer, "%d\r\n", degree());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'e': {                           // reset encoder
        sprintf(buffer, "%d\r\n", encoder_reset());
        NU32_WriteUART3(buffer);
        break;
      }

      case 'f': {                           // set PWM
        MODE = PWM;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &duty_cycle);
        break;
      }

      case 'g': {                           // set current gain
        MODE = ITEST;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &kI);
        break;
      }

      case 'h': {                           // get current gain
        MODE = ITEST;
        sprintf(buffer,"%d\r\n", kI);
        NU32_WriteUART3(buffer);
        break;
      }

      case 'n': {                           // dummy command for demonstration purposes
        int n = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n);
        sprintf(buffer,"%d\r\n", n + 1);
        NU32_WriteUART3(buffer);
        break;
      }

      case 'p': {                           // quit
        MODE = IDLE;
        get_mode(MODE);
        break;
      }

      case 'q': {                           // quit
        MODE = IDLE;
        break;
      }

      case 'r': {                           // returns mode
        get_mode(MODE);
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
