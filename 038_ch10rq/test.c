#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  int m0[4] = {0, 1, 2, 3};
  int m1[4] = {4, 5, 6, 7};
  int m2[4] = {8, 9, 10, 11};
  int * myMatrix[3] = {m0, m1, m2};

  int x = sizeof(myMatrix);
  printf("%d\n", x);
}
