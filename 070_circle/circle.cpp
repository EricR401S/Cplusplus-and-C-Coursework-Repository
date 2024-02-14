#include "circle.hpp"

#include <assert.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

Circle::Circle() : center(Point()), radius(0) {
}

Circle::Circle(Point some_point, double r) : center(some_point), radius(r) {
}

void Circle::move(double dx, double dy) {
  // moves the center of the cirlce by dx and dy
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // calculates the intersection area of a circle

  double d = center.distanceFrom(otherCircle.center);

  if (d >= radius + otherCircle.radius) {
    return 0;
  }

  else if (d <= (radius - otherCircle.radius)) {
    return M_PI * pow(otherCircle.radius, 2);
  }

  else if (d <= (otherCircle.radius - radius)) {
    return M_PI * pow(radius, 2);
  }

  else {
    // the exceptions
    // consider assert here
    assert(((radius - otherCircle.radius) < d) && (d < (radius + otherCircle.radius)));

    double d1 = (pow(radius, 2) - pow(otherCircle.radius, 2) + pow(d, 2)) / (2 * d);

    double d2 = d - d1;

    double Area =
        (pow(radius, 2) * acos(d1 / radius) - d1 * sqrt(pow(radius, 2) - pow(d1, 2)) +
         pow(otherCircle.radius, 2) * acos(d2 / otherCircle.radius) -
         d2 * sqrt(pow(otherCircle.radius, 2) - pow(d2, 2)));

    return Area;
  }
}
