#ifndef __circle_H__
#define __circle_H__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.hpp"

class Circle {
 private:
  Point center;

  const double radius;

 public:
  Circle();
  Circle(Point some_point, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
