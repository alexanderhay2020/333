#include <stdio.h>

int main(void){
  char a, *bp;
  short c;
  int d;
  long e;
  float f;
  double g, jp;
  long double h, *ip;

  printf("Size of char:                  %2ld bytes\n", sizeof(a));
  printf("Size of char pointer:          %2ld bytes\n", sizeof(bp));
  printf("Size of short int:             %2ld bytes\n", sizeof(c));
  printf("Size of int:                   %2ld bytes\n", sizeof(d));
  printf("Size of long int:              %2ld bytes\n", sizeof(e));
  printf("Size of float:                 %2ld bytes\n", sizeof(f));
  printf("Size of double:                %2ld bytes\n", sizeof(g));
  printf("Size of long double:           %2ld bytes\n", sizeof(h));
  printf("Size of long double pointer:   %2ld bytes\n", sizeof(ip));
  printf("Size of double pointer:        %2ld bytes\n", sizeof(jp));

  return 0;
}

/*

char r[10] - creates array of size 10 of type char

&r[0] = r
&r[1] = r + 1

*r = r[0]
*(r+1) = r[1]
*r+1 = r[0] + 1

*/
