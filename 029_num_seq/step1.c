#include <stdio.h>
#include <stdlib.h>

// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
int seq1(int x) {
  int ans = -3;
  const int diff = 4;
  //if x is 0, no further handling
  if (x == 0) {
    return ans;
  }
  //else, just add or subtract x of difference
  else {
    ans += x * diff;
  }
  return ans;
}
//  Step 1 (B): write main to test seq1

//  Step 1 (C): write printSeq1Range
void printSeq1Range(int low, int high) {
  for (int i = low; i < high; i++) {
    int ans = seq1(i);
    // if met the last element, no comma after it
    if (i == high - 1) {
      printf("%d", ans);
    }
    // else, print comma and space after it
    else {
      printf("%d, ", ans);
    }
  }
  // print a \n at the end no matter what
  printf("\n");
}
//  Step 1 (D): add test cases to main to test printSeq1Range

int main(void) {
  // test all cases for seq1 from -4 to 10 inclusively
  for (int i = -4; i < 11; i++) {
    int ans = seq1(i);
    printf("seq1(%d) = %d\n", i, ans);
  }
  // test some cases for range
  printf("printSeq1Range(%d, %d)\n", 0, 4);
  printSeq1Range(0, 4);
  printf("printSeq1Range(%d, %d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  return EXIT_SUCCESS;
}
// Be sure to #include any header files you need!
