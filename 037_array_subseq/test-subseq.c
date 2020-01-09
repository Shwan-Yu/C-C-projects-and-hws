#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t length = maxSeq(array, n);
  printf("%ld = %ld?\n", length, expected_ans);
  if (length != expected_ans) {
    printf("failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int t1[4] = {1, 3, 2, 4};
  run_check(t1, 4, 2);
  int t2[4] = {1, 1, 2, 4};
  run_check(t2, 4, 3);
  int t3[4] = {1, -100, 2, 4};
  run_check(t3, 4, 3);
  int t4[4] = {0, 0, 0, 0};
  run_check(t4, 4, 1);
  int t5[4] = {0, 0, 0, 1};
  run_check(t5, 4, 2);
  int t6[1] = {1};
  run_check(t6, 1, 1);
  int t7[4] = {0, 0, 0, 0};
  run_check(t7, 4, 1);

  exit(EXIT_SUCCESS);
}
