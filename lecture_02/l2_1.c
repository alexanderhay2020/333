#include <stdio.h>

int main(void){
  int i;
  float f;
  double d;
  char c;

  i = 32;
  f = 4.278;
  d = 4.278;
  c = 'k'; //this assigns c as 107 according to ASCII table

  printf("Formatted Output:\n"); // \n means new line
  printf(" i =%4d c = '%c'\n", i, c); // %4d prints integer with 4 spaces
                                      // each % sign has a variable assc. w/ it later on
                                      // %d means it is printed as integer
                                      // %c means it is printed as character

  printf(" f = %19.17f\n", f);  // f\n means it will be printed as a floating point number
                                // %19.17 means it will have 19 space, 17 after decimal

  printf(" d = %19.17lf\n", d); // lf\n means it will be printed as a long floating point number

  return 0;
}
