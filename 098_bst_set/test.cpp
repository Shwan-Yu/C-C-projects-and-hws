#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> bs;
  bs.add(10);
  bs.add(5);
  bs.add(20);
  bs.add(60);
  std::cout << bs.contains(20) << std::endl;
  std::cout << bs.contains(60) << std::endl;
  bs.remove(20);
  std::cout << bs.contains(60) << std::endl;
  std::cout << bs.contains(20) << std::endl;
}
