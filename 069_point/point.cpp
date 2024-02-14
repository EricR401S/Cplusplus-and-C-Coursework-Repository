#include "point.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

// write the point implementation here

Point::Point() : x(0), y(0) {
}

Point::Point(double init_x, double init_y) : x(init_x), y(init_y) {
}

void Point::move(double dx, double dy) {
  // move the Point by dx and dy

  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  // compute distance from other Point p
  double x_diff_squared;
  double y_diff_squared;
  double ans;
  x_diff_squared = pow(x - p.x, 2);
  y_diff_squared = pow(y - p.y, 2);
  ans = sqrt(x_diff_squared + y_diff_squared);
  return ans;
}

// finish
