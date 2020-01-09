#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
  long num;

 public:
  explicit NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
  virtual long evaluate() const { return num; };
  virtual ~NumExpression() {}
};

class CalculateExpression : public Expression {
 protected:
  const char op;
  Expression * l;
  Expression * r;

 public:
  CalculateExpression(const char operation, Expression * lhs, Expression * rhs) :
      op(operation),
      l(lhs),
      r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << l->toString() << ' ' << op << ' ' << r->toString() << ')';
    return ss.str();
  }

  virtual long evaluate() const = 0;

  virtual ~CalculateExpression() {
    delete l;
    delete r;
  }
};

class PlusExpression : public CalculateExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) :
      CalculateExpression('+', lhs, rhs) {}
  virtual long evaluate() const {
    long ret = l->evaluate() + r->evaluate();
    return ret;
  }

  virtual ~PlusExpression() {}
};

class MinusExpression : public CalculateExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) :
      CalculateExpression('-', lhs, rhs) {}

  virtual long evaluate() const {
    long ret = l->evaluate() - r->evaluate();
    return ret;
  }
  virtual ~MinusExpression() {}
};

class TimesExpression : public CalculateExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) :
      CalculateExpression('*', lhs, rhs) {}
  virtual long evaluate() const {
    long ret = l->evaluate() * r->evaluate();
    return ret;
  }

  virtual ~TimesExpression() {}
};

class DivExpression : public CalculateExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) :
      CalculateExpression('/', lhs, rhs) {}
  virtual long evaluate() const {
    long ret = l->evaluate() / r->evaluate();
    return ret;
  }
  virtual ~DivExpression() {}
};
