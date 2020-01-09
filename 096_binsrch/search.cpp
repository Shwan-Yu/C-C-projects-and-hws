#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high) {
    return low;
  }
  int mid;
  int mid_val;
  while (low < high - 1) {
    mid = (low + high) / 2;
    mid_val = f->invoke(mid);
    if (mid_val == 0) {
      return mid;
    }
    else if (mid_val < 0) {
      low = mid;
    }
    else {
      high = mid;
    }
  }
  return low;
}
