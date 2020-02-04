// with NU32 library

#include "NU32.h"
#include <stdio.h>

int main(void){
  NU32_Startup();
  NU32_LED1 = 1; // 0=on, 1=off
  NU32_LED2 = 0;

  char outstring[100];
  int count = 0;

  while(1){
    while(NU32_USER){
      NU32_LED1 = NU32_USER;
      NU32_LED2 = !NU32_USER;
      if(NU32_USER==0){
        count = count+1;
        sprintf(outstring, "Pressed %3d times!", count);
        NU32_WriteUART3(outstring);
        NU32_WriteUART3("\r\n");
      }
    }
  }
  return 0;
}
