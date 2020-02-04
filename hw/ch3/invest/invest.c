#include <stdio.h>
#include "NU32.h"                                                  // added
#define MAX_YEARS 100
#define MAX_MESSAGE_LENGTH 20


typedef struct {
  double inv0;
  double growth;
  int years;
  double invarray[MAX_YEARS+1];
} Investment;


int getUserInput(Investment *invp){
  int valid;
  char message[MAX_MESSAGE_LENGTH];   // added

  NU32_WriteUART3("Enter investment, growth rate, number of years");    // changed from printf
  NU32_WriteUART3("\r\n");                                              // added
  NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);                          // added
  sscanf(message, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));
  NU32_WriteUART3(message);                                             // added
  NU32_WriteUART3("\r\n");                                              // added
  valid = (invp->inv0 > 0) && (invp->growth > 0) && (invp->years > 0) && (invp->years <= MAX_YEARS);

  // this is being weird
  // NU32_WriteUART3("Valid input?");
  // NU32_WriteUART3(valid);
  return(valid);
}


void calculateGrowth(Investment *invp){
  int i;

  for(i=1; i<= invp->years; i=i+1){
    invp->invarray[i] = invp->growth * invp->invarray[i-1];
  }
}


void sendOutput(double *arr, int yrs){
  int i;
  char outstring[100];

  NU32_WriteUART3("\r\nRESULTS:\r\n");                                  // changed; added return carriage tag

  for(i=0; i<=yrs;i++){
    sprintf(outstring, "Year %3d:   %10.2f\r\n", i, arr[i]);

    NU32_WriteUART3(outstring);                                         // changed from printf
  }

  NU32_WriteUART3("\r\n");                                              // added
}


int main(void){
  Investment inv;
  NU32_Startup();                                                       // added

  while(getUserInput(&inv)){
    inv.invarray[0] = inv.inv0;
    calculateGrowth(&inv);
    sendOutput(inv.invarray, inv.years);

  }

  return 0;
}
