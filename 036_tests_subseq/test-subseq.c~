#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

unsigned f(unsigned x, unsigned y) {
  return 3;
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  //unsigned ans = f(x, y);
  printf("%i ?= %i\n", ans, expected_ans);
  if (ans != expected_ans) {
    printf("failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  //run_check(0, 1, 0);
  run_check(1, 0, 1);
  //run_check(1, 1, 1);
  run_check(6, 2, 36);
  //run_check(1, 3, 1);
  //run_check(1, 4, 1);
  //run_check(2, 0, 1);
  run_check(0, 0, 1);
  run_check(2147483647, 1, 2147483647);
  exit(EXIT_SUCCESS);
}
