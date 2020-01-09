#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> bm;
  bm.add(10, 11);
  bm.add(5, 6);
  bm.add(20, 21);
  bm.add(60, 61);
  std::cout << bm.lookup(20) << std::endl;
  std::cout << bm.lookup(60) << std::endl;
  bm.remove(20);
  std::cout << bm.lookup(60) << std::endl;
  BstMap<int, int> bm2 = bm;
  BstMap<int, int> bm3;
  bm3 = bm;
  bm.remove(5);
  std::cout << bm2.lookup(5) << std::endl;
  std::cout << bm3.lookup(5) << std::endl;
}
