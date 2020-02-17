#include <stdio.h>


void char_ops(char c1, char c2, char c3){
  char outstring[100];

  c3 = c1 + c2;
  printf("char addition: %i \r\n", c3);            // operation makes c3 an int

  c3 = c1 - c2;
  printf("char subtraction: %i \r\n", c3);

  c3 = c1 * c2;
  printf("char multiplication: %i \r\n", c3);

  c3 = c1 / c2;
  printf("char division: %i \r\n", c3);

  printf("\n");
}


void int_ops(int i1, int i2, int i3){
  char outstring[100];

  i3 = i1 + i2;
  printf("int addition: %i \r\n", i3);

  i3 = i1 - i2;
  printf("int subtraction: %i \r\n", i3);

  i3 = i1 * i2;
  printf("int multiplication: %i \r\n", i3);

  i3 = i1 / i2;
  printf("int division: %i \r\n", i3);

  printf("\n");
}


void long_ops(long int j1, long int j2, long int j3){
  char outstring[100];

  j3 = j1 + j2;
  printf("long addition: %li \r\n", j3);

  j3 = j1 - j2;
  printf("long subtraction: %li \r\n", j3);

  j3 = j1 * j2;
  printf("long multiplication: %li \r\n", j3);

  j3 = j1 / j2;
  printf("long division: %li \r\n", j3);

  printf("\n");
}


void float_ops(float f1, float f2, float f3){
  char outstring[100];

  f3 = f1 + f2;
  printf("float addition: %f \r\n", f3);

  f3 = f1 - f2;
  printf("float subtraction: %f \r\n", f3);

  f3 = f1 * f2;
  printf("float multiplication: %f \r\n", f3);

  f3 = f1 / f2;
  printf("float division: %f \r\n", f3);

  printf("\n");
}


void dbl_ops(long double d1, long double d2, long double d3){
  char outstring[100];

  d3 = d1 + d2;
  printf("double addition: %Lf \r\n", d3);

  d3 = d1 - d2;
  printf("double subtraction: %Lf \r\n", d3);

  d3 = d1 * d2;
  printf("double multiplication: %Lf \r\n", d3);

  d3 = d1 / d2;
  printf("double division: %Lf \r\n", d3);

  printf("\n");
}


void main(void){

  printf("\n");

  char c1=5, c2=6, c3;
  int i1=5, i2=6, i3;
  long long int j1=5, j2=6, j3;
  float f1=1.01, f2=2.02, f3;
  long double d1=1.01, d2=2.02, d3;

  char_ops(c1, c2, c3);
  int_ops(i1, i2, i3);
  long_ops(j1, j2, j3);
  float_ops(f1, f2, f3);
  dbl_ops(d1, d2, d3);
}
