#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t len = 1;
  size_t max_len = 1;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      len++;
      if (len > max_len) {
        max_len = len;
      }
    }
    else {
      len = 1;
    }
  }
  return max_len;
}
