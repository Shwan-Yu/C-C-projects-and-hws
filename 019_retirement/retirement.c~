#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int months;
  double contribution;
  double rate_of_return;
} retire_info;
//(1) an int called "months" for the number of months it is applicable to,
//(2) a double called "contribution" for how many dollars
//are contributed (or spent if negative) from the account per month
//(3) a double called "rate_of_return" for the rate of returns

double calculate(double balance, double returns, double contribution) {
  return balance + (balance * returns + contribution);
}

double workOrRetire(retire_info status, int startAge, double initial) {
  int months = status.months;
  double contribution = status.contribution;
  double rate_of_return = status.rate_of_return;
  double balance = initial;
  for (int i = startAge; i < startAge + months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i, balance);
    balance = calculate(balance, rate_of_return, contribution);
  }
  return balance;
}

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired
  double balance = initial;
  balance = workOrRetire(working, startAge, balance);
  balance = workOrRetire(retired, startAge + working.months, balance);
}

int main(void) {
  int startAge = 327;                             //in months
  double initial = 21345;                         //initial savings in dollars
  retire_info working = {489, 1000, 0.045 / 12};  //info about working
  retire_info retired = {384, -4000, 0.01 / 12};
  retirement(startAge,  //in months
             initial,   //initial savings in dollars
             working,   //info about working
             retired);
  return EXIT_SUCCESS;
}
