/*
text goes here
*/

// Preprocessor Commands
#include <stdio.h>
#define MAX_YEARS 100 //defines constant; unchangeable

// Datatype Definitions
typedef struct { //defines new datatype "Investment" as a structure
  double inv0;
  double growth;
  int years;
  double invarray[MAX_YEARS+1]; //array with 101 elements of type double
} Investment;

// Function Prototypes
int getUserInput(Investment *invp); //*invp is pointer to type investent, returns integer
void calculateGrowth(Investment *invp); //*invp is pointer to type investent, no return
void sendOutput(double *arr, int years); //*arr is pointer to type double, an address within an array

// Main Function
int main(void){

  Investment inv; //variable inv of type investment

  while(getUserInput(&inv)){
    inv.invarray[0] = inv.inv0; //inv.invarray is the array defined within the new datatype, within the variable inv
    // sets first index of array to initial investment

    calculateGrowth(&inv); // fills inv with investment over years
    sendOutput(inv.invarray, inv.years);
  }
  return 0;
}

// Subfunctions
void calculateGrowth(Investment *invp){ // *invp is a pointer to type Investment
  int i;

  for(i=1; i<= invp->years; i=i+1){ // initialize i, test if i is less than number of years, increment
  // invp->years invp points to the years within the structure of Investment
  // would be same as inv.years if inv was passed instead of the address
    invp->invarray[i] = invp->growth * invp->invarray[i-1];
  }
}

int getUserInput(Investment *invp){
  int valid;

  printf("Enter investment, growth rate, number of years (up to %d): ", MAX_YEARS);

  scanf("%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));
  // &(invp->inv0) points to address of initial investment
  // &(invo->growth) points to address of growth
  // etc

  valid = (invp->inv0 > 0) && (invp->growth > 0) && (invp->years > 0) && (invp->years <= MAX_YEARS);
  // boolean and (&&)
  // checks if each value is true; if true, returns 1; if false, returns 0
  // this is why valid, while representing boolean logic, is an integer

  printf("Valid input? %d\n", valid);
  if(!valid){
    printf("Invalid input; exiting.\n");
  }
  return(valid);
}

void sendOutput(double *arr, int yrs){

  int i;
  char outstring[100]; // array w/ 100 elements of type char
  // this array is a string, a character string

  printf("\nRESULTS:\n\n");
  for(i=0; i<=yrs;i++){ // initialize i as 0, condition, increment i
    sprintf(outstring, "Year %3d:   %10.2f\n", i, arr[i]);
    // populates outstring

    printf("%s", outstring); // %s looks for string variable or array of characters
  }
  printf("\n");
}
