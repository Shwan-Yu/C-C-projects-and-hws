#include <stdio.h>
#include <stdlib.h>
// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
int seq3(int x, int y) {
  int ans = 0;
  //if x and y is 0, no further handling
  if (x == 0 && y == 0) {
    return ans;
  }
  //else, grab the value at x,0 first, then add to position x,y
  else {
    ans += -3 * x;
    ans += y * (x + 2);
  }
  return ans;
}
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int countEven = 0;
  //loop through the range
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      //no need to take abs here, but just to be consistent with step2,
      //taking an abs and do the mod makes it more clear.
      //even case
      if (abs(seq3(i, j)) % 2 == 0) {
        countEven++;
      }
      //not even case
      else {
        continue;
      }
    }
  }
  return countEven;
}
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range

int main(void) {
  // test all cases for seq3
  for (int i = -5; i < 6; i++) {
    for (int j = -5; j < 6; j++) {
      int ans = seq3(i, j);
      printf("seq3(%d, %d) = %d\n", i, j, ans);
    }
  }
  // test some cases for range
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         2,
         0,
         3,
         countEvenInSeq3Range(0, 2, 0, 3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         3,
         0,
         5,
         2,
         countEvenInSeq3Range(3, 5, 0, 2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         3,
         3,
         5,
         2,
         countEvenInSeq3Range(3, 5, 3, 2));
  return EXIT_SUCCESS;
}
// Be sure to #include any header files you need!
