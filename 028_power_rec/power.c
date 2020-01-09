#include <stdio.h>
#include <stdlib.h>

unsigned powerHelper(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else {
    return x * powerHelper(x, y - 1);
  }
}

unsigned power(unsigned x, unsigned y) {
  return powerHelper(x, y);
}
