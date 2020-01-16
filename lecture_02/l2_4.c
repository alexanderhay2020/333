#include <stdio.h>

void printRatio(int numer, int denom){

  double ratio;

  //ex 1
  ratio = numer/denom;
  printf("Ratio, %1d/%1d:                     %5.2lf\n",numer,denom,ratio);

  //ex 2
  ratio = numer/((double) denom);
  printf("Ratio, %1d/((double)%1d):           %5.2lf\n",numer,denom,ratio);

  //ex 3
  ratio = ((double) numer)/((double) denom);
  printf("Ratio, ((double)%1d)/((double)%1d): %5.2lf\n",numer,denom,ratio);

  // ((double)denom) typecasts denom, an integer, as a double.
  // denom does NOT change to double, it stays an integer

  // ex 2 has both implicit and expicit type conversions
  // ((double) denom) is explicit
  // numer/((double) denom) is implicit
  // numer has to be double because both ratio and denom are doubles

  //promotion - char to int, int to float, etc
}

int main(void){
  int num = 5, den = 2;
  printRatio(num,den);

  return 0;
}
