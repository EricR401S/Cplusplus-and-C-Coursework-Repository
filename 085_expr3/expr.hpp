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

  virtual long evaluate() const = 0;

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

  virtual long evaluate() const { return num; };
};

class OPExpression : public Expression {
 protected:
  Expression * lhs;

  Expression * rhs;

  std::string designated_operator;

 public:
  OPExpression(Expression * nlhs, Expression * nrhs) : lhs(nlhs), rhs(nrhs) {}

  virtual ~OPExpression() {
    delete lhs;
    delete rhs;
  }

  std::string toString() const {
    std::stringstream ss;

    ss << '(' << lhs->toString() << " " + designated_operator + " " << rhs->toString()
       << ")";

    return ss.str();
  }
};

class PlusExpression : public OPExpression {
 public:
  PlusExpression(Expression * nlhs, Expression * nrhs) : OPExpression(nlhs, nrhs) {
    designated_operator = "+";
  }

  // virtual ~PlusExpression() {
  //   delete lhs;
  //   delete rhs;
  // }

  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); };
};

class MinusExpression : public OPExpression {
 public:
  MinusExpression(Expression * nlhs, Expression * nrhs) : OPExpression(nlhs, nrhs) {
    designated_operator = "-";
  }

  // virtual ~PlusExpression() {
  //   delete lhs;
  //   delete rhs;
  // }

  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); };
};

class TimesExpression : public OPExpression {
 public:
  TimesExpression(Expression * nlhs, Expression * nrhs) : OPExpression(nlhs, nrhs) {
    designated_operator = "*";
  }

  // virtual ~PlusExpression() {
  //   delete lhs;
  //   delete rhs;
  // }

  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); };
};

class DivExpression : public OPExpression {
 public:
  DivExpression(Expression * nlhs, Expression * nrhs) : OPExpression(nlhs, nrhs) {
    designated_operator = "/";
  }

  // virtual ~PlusExpression() {
  //   delete lhs;
  //   delete rhs;
  // }

  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); };
};

#endif
