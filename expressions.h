#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <memory>
#include <iostream>
#include <string>

struct IExpression {
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

struct Constant : public IExpression {
  int value;
  explicit Constant(int val) : value(val) {}
  int Calculate() const override {
    return value;
  }
};

struct IUnaryOperation : public IExpression {
  std::unique_ptr<IExpression> op_;
  IUnaryOperation(std::unique_ptr<IExpression> op) : op_(std::move(op)) {} //NOLINT
  virtual int Operation(int op) const = 0;
  int Calculate() const override {
    return Operation(op_->Calculate());
  }
};

struct IBinaryOperation : public IExpression {
  std::unique_ptr<IExpression> lhs_;
  std::unique_ptr<IExpression> rhs_;
  IBinaryOperation(std::unique_ptr<IExpression> lhs, std::unique_ptr<IExpression> rhs)
    : lhs_(std::move(lhs))
    , rhs_(std::move(rhs)) {
  }
  virtual int Operation(int lhs, int rhs) const = 0;
  int Calculate() const override {
    return Operation(this->lhs_->Calculate(), this->rhs_->Calculate());
  }
};

struct Sum : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return lhs + rhs;
  }
};

struct Subtract : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return lhs - rhs;
  }
};

struct Multiply : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return lhs * rhs;
  }
};

struct Divide : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return lhs / rhs;
  }
};

struct Residual : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return lhs % rhs;
  }
};

struct Minimum : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return std::min(lhs, rhs);
  }
};

struct Maximum : public IBinaryOperation {
  using IBinaryOperation::IBinaryOperation;
  int Operation(int lhs, int rhs) const override {
    return std::max(lhs, rhs);
  }
};

struct AbsoluteValue : public IUnaryOperation {
  using IUnaryOperation::IUnaryOperation;
  int Operation(int operand) const override {
    return std::abs(operand);
  }
};

struct Square : public IUnaryOperation {
  using IUnaryOperation::IUnaryOperation;
  int Operation(int operand) const override {
    return operand * operand;
  }
};

int CalculatePolishNotation(std::string_view input);

#endif