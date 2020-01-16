
// Q4: Given the following structure, declare variable of type s and initialize each value to 0
typedef struct{
  unsigned int userId;
  unsigned char classId;
  unsigned int year;
  char name[100];
} student;

// A4
student s;
s.userId = 0;
s.classId = 0;
s.year = 0;

// A5


// A6

student *sp //pointer to type student
sp = &s //pointes to student
user(sp)
printf("y=%d m=%c", sp->year, sp->name[0])

void user(student *sp){
  printf("type in year and name");
  scanf("%d %s", &sp->year, &sp->name[0]);

  scanf(%d, &i); //scanf uses addresses
  printf(%d, i); //printf uses variables

void printC1(bigc*) // pass-by pointer, requires 1 copy of bigC
void printC2(bigC) // pass-by value, requires 2 copies of bigC

// Q9 write a program that uses a while loop to ask the user for a value between -5 and 5.
// if number is within range, store it. loop until 10 values are stored

// A9
#include <stdio.h>

int main (){
  int n[10];
  int i=0;
  int temp;

  // crude loop
  for(i,i<10,i++){
    printf("enter number");
    scanf("%d", &n[i]);
  }

  // better loop
  while(i<10){
    printf("enter number");
    scanf("%d", &temp);
    if((temp>-5) && (temp<5)){
      n[i]=temp;
      i++;
    }
  }
}
