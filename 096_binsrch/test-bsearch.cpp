#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class LinFn : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class NegFn : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -100; }
};

class PosFn : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 100; }
};

//test case in next-README
class SinFn : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max_times;
  if (low >= high) {
    max_times = 1;
  }
  else {
    max_times = log(high - low) / log(2) + 1;
  }
  Function<int, int> * cf = new CountedIntFn(max_times, f, mesg);
  int ans = binarySearchForZero(cf, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Wrong answers in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main() {
  Function<int, int> * l = new LinFn();
  Function<int, int> * pos = new PosFn();
  Function<int, int> * neg = new NegFn();
  Function<int, int> * sin = new SinFn();

  check(l, 0, 0, 0, "Linear Function1");
  check(l, 2, 5, 2, "Linear Function2");
  check(l, -2, 5, 0, "Linear Function3");
  check(l, -2, 0, -1, "Linear Function4");
  check(l, -2, 1000000000, 0, "Linear Function5");
  check(l, -100000000, -10000, -10001, "Linear Function6");
  check(l, -100000000, 50000000, 0, "Linear Function7");

  check(pos, -2, 5, -2, "Pos Function");
  check(pos, -2, 10000000, -2, "Pos Function");
  check(pos, -20000000, 5, -20000000, "Pos Function");
  check(pos, -20000000, 10000000, -20000000, "Pos Function");

  check(neg, -2, 5, 4, "Neg Function");
  check(neg, -2, 10000000, 9999999, "Neg Function");
  check(neg, -20000000, 5, 4, "Neg Function");
  check(neg, -20000000, 10000000, 9999999, "Neg Function");
  check(sin, 0, 150000, 52359, "Sin Function");
}
