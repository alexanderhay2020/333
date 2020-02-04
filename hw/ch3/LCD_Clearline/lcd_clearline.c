#include <stdio.h>
#include "NU32.h"
#include "LCD.h"

int main(void){

  NU32_Startup();

  while(1){
    NU32_WriteUART3("PRESS BUTTON TO CLEAR LINE");
    NU32_WriteUART3("\r\n");
    while(PORTDbits.RD7) {
        LCD_Clear()
    }
  }
  return 0;
}
