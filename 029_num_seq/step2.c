#include <stdio.h>
#include <stdlib.h>

// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
int seq2(int x) {
  int ans = 1;
  //if x is 0, no further handling
  if (x == 0) {
    return ans;
  }
  // if the abs(x)%4 is 2, no matter x is positive or negative, ans = 2x
  else if (abs(x) % 4 == 2) {
    ans = 2 * x;
  }
  // else just add x*(x+3)
  else {
    ans += x * (x + 3);
  }
  return ans;
}
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
int sumSeq2(int low, int high) {
  int sum_all = 0;
  for (int i = low; i < high; i++) {
    int ans = seq2(i);
    // add them all
    sum_all += ans;
  }
  return sum_all;
}
//  Step 2 (D): add test cases to main to test sumSeq2
int main(void) {
  // test all cases for seq2 from -4 to 14 inclusively
  for (int i = -4; i < 15; i++) {
    int ans = seq2(i);
    printf("seq2(%d) = %d\n", i, ans);
  }
  // test some cases for sum
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", 0, 0, sumSeq2(0, 0));
  return EXIT_SUCCESS;
}
// Be sure to #include any header files you need!
