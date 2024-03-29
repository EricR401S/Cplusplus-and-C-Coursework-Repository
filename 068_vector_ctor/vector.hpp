#ifndef __myvector_H__
#define __myvector_H__
#include <stdio.h>
#include <stdlib.h>

class Vector2D {
 private:
  double x;
  double y;

 public:
  Vector2D();
  Vector2D(double init_x, double init_y);
  // void initVector(double init_x, double init_y);
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);
  double dot(const Vector2D & rhs) const;
  void print() const;
};

#endif
