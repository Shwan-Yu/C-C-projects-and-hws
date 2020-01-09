#include "circle.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

Circle::Circle(Point init_c, double init_r) : c(init_c), r(init_r) {
}
void Circle::move(double dx, double dy) {
  c.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = c.distanceFrom(otherCircle.c);
  double r1 = std::min(r, otherCircle.r);
  double r2 = std::max(r, otherCircle.r);
  if (d < (r1 + r2)) {
    double a = r1 * r1;
    double b = r2 * r2;
    double angle1 = acos((a + d * d - b) / (2.0 * r1 * d)) * 2.0;
    double angle2 = acos((b + d * d - a) / (2.0 * r2 * d)) * 2.0;
    if (d <= r2 - r1) {
      return M_PI * a;
    }
    return (a * (angle1 - sin(angle1)) + b * (angle2 - sin(angle2))) * 0.5;
  }
  return 0.0;
}
