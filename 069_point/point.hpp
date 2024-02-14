#ifndef __myPoint_H__
#define __myPoint_H__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Point {
 private:
  double x;
  double y;

 public:
  Point();
  Point(double init_x, double init_y);
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

#endif
