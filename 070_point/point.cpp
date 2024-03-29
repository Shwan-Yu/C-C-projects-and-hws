#include "point.h"

#include <cmath>
#include <cstdio>

Point::Point() : x(0), y(0) {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return pow((pow((x - p.x), 2) + pow((y - p.y), 2)), 0.5);
}
