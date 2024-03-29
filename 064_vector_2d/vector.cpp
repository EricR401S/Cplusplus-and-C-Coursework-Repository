#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
// std means functions live in standard scope
// so you access them through std
//
void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
  return;
}

double Vector2D::getMagnitude() const {
  double ans = 0.0;
  ans = std::sqrt((std::pow(x, 2) + std::pow(y, 2)));
  return ans;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  //ans.initVector(0, 0);
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
  //- Vector2D operator+(const Vector2D & rhs) const;
  //The overloaded + operator should do vector addition in the usual
  //way and return a copy of the new vector. Think about why the
  //parameter should be const.
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;

  y += rhs.y;

  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double ans = 0.0;

  ans = x * rhs.x + y * rhs.y;

  return ans;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
  return;
}
