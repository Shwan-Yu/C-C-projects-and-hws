#include <iostream>

#include "IntMatrix.h"
int main(void) {
  std::cout << "start\n";
  IntMatrix a(4, 5);
  std::cout << "init\n";
  for (int i = 0; i < a.getRows(); i++) {
    for (int j = 0; j < a.getColumns(); j++) {
      a[i][j] = i + j;
      std::cout << a[i][j] << "," << i << "," << j << "\n";
    }
  }
  std::cout << "a is:\n" << a << std::endl;
  IntMatrix b(a);
  std::cout << "b is:\n" << a << std::endl;
  if (a == b) {
    std::cout << "a and b have the same contents" << std::endl;
  }
  else {
    std::cout << "a and b have different contents" << std::endl;
  }
  for (int i = 0; i < b.getRows(); i++) {
    for (int j = 0; j < b.getColumns(); j++) {
      b[i][j] += i * j;
    }
  }
  std::cout << "Now, b is:\n" << b << std::endl;
  if (a == b) {
    std::cout << "a and b have the same contents" << std::endl;
  }
  else {
    std::cout << "a and b have different contents" << std::endl;
  }

  IntMatrix c;
  std::cout << c.getRows() << std::endl;
  std::cout << "c is:\n" << c << std::endl;
  c = a + b;
  std::cout << "Now, c is:\n" << c << std::endl;
  return EXIT_SUCCESS;
}
