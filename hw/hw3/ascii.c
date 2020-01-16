#include <stdio.h>

int main(void){

  int i;

  for(i=33;i<128;i++){
    printf(" value =%3d c = '%c'\n", i, ((char)i));
  }

  return 0;
}
