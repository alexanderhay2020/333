#include <xc.h>
#include <stdio.h>
#include "NU32.h"
#include "encoder.h"

#define BUF_SIZE 200


static int encoder_command(int read){
  SPI4BUF = read;
  while (!SPI4STATbits.SPIRBF) { ; }
  SPI4BUF;
  SPI4BUF = 5;
  while (!SPI4STATbits.SPIRBF) { ; }
  return SPI4BUF;
}


int encoder_counts(void) {
  // encoder_command(1);
  return encoder_command(1);
}


int encoder_reset(void) {
  return encoder_command(0);
}


void encoder_init(void) {
  SPI4CON = 0;
  SPI4BUF;
  SPI4BRG = 0x4;
  SPI4STATbits.SPIROV = 0;
  SPI4CONbits.MSTEN = 1;
  SPI4CONbits.MSSEN = 1;
  SPI4CONbits.MODE16 = 1;
  SPI4CONbits.MODE32 = 0;
  SPI4CONbits.SMP = 1;
  SPI4CONbits.ON = 1;
}


int degree(void){
  int count = 360*(encoder_counts() - 32768);
  int deg = count/384;
  return deg;
}
