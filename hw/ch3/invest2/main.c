#include <stdio.h>
#include "NU32.h"                                                       // added
#include "helper.h"                                                     // added

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
