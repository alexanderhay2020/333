#include <xc.h>
#include <stdio.h>
#include "NU32.h"          // config bits, constants, funcs for startup and UART
#include "utilities.h"


void get_mode(modes m){
  char buffer[30];

  switch (m) {

    case IDLE: {                           // read encoder counts
      sprintf(buffer,"Mode set: IDLE\r\n");
      NU32_WriteUART3(buffer);            // send encoder count to client
      break;
    }

    case PWM: {                           // read encoder counts
      sprintf(buffer,"Mode set: PWM\r\n");
      NU32_WriteUART3(buffer);            // send encoder count to client
      break;
    }

    case ITEST: {                           // read encoder degrees
      sprintf(buffer,"Mode set: ITEST\r\n");
      NU32_WriteUART3(buffer);            // send encoder count to client
      break;
    }

    case HOLD: {                           // read encoder degrees
      sprintf(buffer,"Mode set: HOLD\r\n");
      NU32_WriteUART3(buffer);            // send encoder count to client
      break;
    }

    case TRACK: {                           // dummy command for demonstration purposes
      sprintf(buffer,"Mode set: TRACK\r\n");
      NU32_WriteUART3(buffer);            // send encoder count to client
      break;
    }
  }
}
