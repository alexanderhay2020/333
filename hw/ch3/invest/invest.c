#include <stdio.h>
#include "NU32.h"          // constants, funcs for startup and UART
#define MAX_YEARS 100
#define MAX_MESSAGE_LENGTH 3


typedef struct {
  double inv0;
  double growth;
  int years;
  double invarray[MAX_YEARS+1];
} Investment;


int main(void){
  Investment inv;
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init

  while(getUserInput(&inv)){
    NU32_WriteUART3("Enter investment, growth rate, number of years");
    NU32_WriteUART3("\r\n");                      // carriage return and newline

  }

  return 0;
}


int getUserInput(Investment *invp){
  int valid;
  char message[MAX_MESSAGE_LENGTH];

  NU32_WriteUART3("Enter investment, growth rate, number of years");

  NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);
  sscanf(message, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));

  valid = (invp->inv0 > 0) && (invp->growth > 0) && (invp->years > 0) && (invp->years <= MAX_YEARS);

  return(valid);
}
