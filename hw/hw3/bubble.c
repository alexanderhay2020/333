#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100 // max length of string input

// Function Prototypes
void getString(char *str);
void printResult(char *str);
int greaterThan(char ch1, char ch2);
void swap(char *str, int index1, int index2);

int main(void){
  int len, i1, i2;
  char str[MAXLENGTH];

  getString(str);
  len = strlen(str);

  for(i1=0; i1<len-1; i1++){
    for(i2=0; i2<len-i1-1; i2++){
      if(greaterThan(str[i2], str[i2+1])==0){
        swap(str, i2, i2+1);
      }
    }
  }
  printResult(str);

  return 0;
}

// Part a
void getString(char *str){

  int valid;

  printf("Enter string\n");
  scanf("%s[^\n]",str);
}

// Part b
void printResult(char *str){
    printf("%s\n", str);
}

// Part c
int greaterThan(char ch1, char ch2){

  int compare;

  compare = (ch1 > ch2);
  return(compare);
}

// Part d
void swap(char *str, int index1, int index2){

  char temp;

  temp = str[index1];
  str[index1] = str[index2];
  str[index2] = temp;

}
