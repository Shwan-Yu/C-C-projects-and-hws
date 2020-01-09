#include "readFreq.h"

#include <stdio.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream ifstr(fname);
  if (ifstr.fail()) {
    perror("Could not open file\n");
    exit(EXIT_FAILURE);
  }
  uint64_t * res = new uint64_t[257]();
  int c;
  while ((c = ifstr.get()) != EOF) {
    res[c]++;
  }
  res[256]++;
  ifstr.close();
  return res;
}
