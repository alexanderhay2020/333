#ifndef helper__H__
#define helper__H__

#define MAX_YEARS 100
#define MAX_MESSAGE_LENGTH 20

typedef struct {
  double inv0;
  double growth;
  int years;
  double invarray[MAX_YEARS+1];
} Investment;

void calculateGrowth(Investment *invp);
int getUserInput(Investment *invp);
void sendOutput(double *arr, int yrs);

#endif // helper__H__
