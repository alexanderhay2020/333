// without NU32 library

#include <xc.h>          // Load the proper header for the processor

int main(void) {
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear

  while(1) {
      while(!PORTDbits.RD7) {
        LATFbits.LATF0 = 0;
      }
      LATFbits.LATF0 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
  }
  return 0;
}
