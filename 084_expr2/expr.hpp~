#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

//YOUR CODE GOES HERE!

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 protected:
  long num;

 public:
  NumExpression(long n) : num(n) {}

  long getNum() { return num; }

  std::string toString() const {
    std::stringstream ss;

    ss << num;

    return ss.str();
  }
};

class PlusExpression : public Expression {
 protected:
  Expression * lhs;

  Expression * rhs;

 public:
  PlusExpression(Expression * nlhs, Expression * nrhs) : lhs(nlhs), rhs(nrhs) {}

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }

  std::string toString() const {
    std::stringstream ss;

    ss << '(' << lhs->toString() << " + " << rhs->toString() << ")";

    return ss.str();
  }
};

#endif
