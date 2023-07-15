#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>
#include <cmath>

class NodeBase {
 public:
  // Make any of these functions virtual, or pure virtual, if necessary.
  NodeBase() = default;
  virtual double eval(double x) const = 0;
  // double eval() const;
  virtual double derivative(double x) const = 0;
  virtual std::string rep() const = 0;
  virtual ~NodeBase() = default;
};

class Expr {
  std::shared_ptr<NodeBase> m_ptr;

  Expr(std::shared_ptr<NodeBase> ptr) : m_ptr{ptr} {}

 public:
  Expr(double value);

  // Add member functions if necessary.
  // double eval() const {
  //     return m_ptr->eval();
  // }
  double eval(double x) const {
      return m_ptr->eval(x);
  }

  std::string rep() const {
      return m_ptr->rep();
  }
  static const Expr x;
  double derivative(double x) const {
      return m_ptr->derivative(x);
  }
  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);


  // Add friend declarations if necessary.
};

class Variable : public NodeBase {
  // Add functions if necessary.
public:
    double eval(double x) const {
        return x;
    }
    std::string rep() const {
        return "x";
    }

    double derivative(double) const {
        return 1;
    }

};

class Constant : public NodeBase {
  double m_value;

  // Add functions if necessary.
  double eval(double) const {
      return m_value;
  }

  // double eval(double x = m_value) const {
  //     // return 1;
  // }

  std::string rep() const {
      return std::to_string(m_value);
  }

  double derivative(double) const {
      return 0;
  }

 public:
  Constant(double value) : m_value{value} {}
};

// Expr::Expr(double value) : m_ptr(std::make_shared<Constant>(value)) {}

class UnaryOperator : public NodeBase {
  char m_op;
  Expr m_operand;

  // Add functions if necessary.
  double eval(double x) const {
      return m_op == '+' ? m_operand.eval(x) : -m_operand.eval(x);
  }
  std::string rep() const {
      return m_op + ('(' + m_operand.rep() + ')');
  }
  double derivative(double x) const {
      return m_op == '+' ? m_operand.derivative(x) : -m_operand.derivative(x);
  }
 public:
  UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
};

class BinaryOperator : public NodeBase {
 protected:
  Expr m_left;
  Expr m_right;

 public:
  BinaryOperator(const Expr &left, const Expr &right)
      : m_left{left}, m_right{right} {}
};

class PlusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  double eval(double x) const {
      return m_left.eval(x) + m_right.eval(x);
  }

  std::string rep() const {
      return '(' + m_left.rep() + ')' + " + " + '(' + m_right.rep() + ')'; 
  }

  double derivative(double x) const {
      return m_left.derivative(x) + m_right.derivative(x);
  }
  // Add functions if necessary.
};

class MinusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
  double eval(double x) const {
      return m_left.eval(x) - m_right.eval(x);
  }

  std::string rep() const {
      return '(' + m_left.rep() + ')' + " - " + '(' + m_right.rep() + ')'; 
  }

  double derivative(double x) const {
      return m_left.derivative(x) - m_right.derivative(x);
  }
};

class MultiplyOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
  double eval(double x) const {
      return m_left.eval(x) * m_right.eval(x);
  }
  std::string rep() const {
      return '(' + m_left.rep() + ')' + " * " + '(' + m_right.rep() + ')'; 
  }

  double derivative(double x) const {
      return m_left.derivative(x) * m_right.eval(x) + m_right.derivative(x) * m_left.eval(x);
  }

};

class DivideOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
  double eval(double x) const {
      return m_left.eval(x) / m_right.eval(x);
  }
  std::string rep() const {
      return '(' + m_left.rep() + ')' + " / " + '(' + m_right.rep() + ')'; 
  }

  double derivative(double x) const {
      return (m_left.derivative(x) * m_right.eval(x) - m_right.derivative(x) * m_left.eval(x)) / pow(m_right.eval(x), 2);
  }
};

const Expr Expr::x{std::make_shared<Variable>()};

Expr::Expr(double value) : m_ptr{std::make_shared<Constant>(value)} {}

Expr operator-(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('-', operand)};
}

Expr operator+(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('+', operand)};
}

Expr operator+(const Expr &left, const Expr &right) {
  // Your code here.
  return {std::make_shared<PlusOp>(left, right)};
}

Expr operator-(const Expr &left, const Expr &right) {
  // Your code here.
  return {std::make_shared<MinusOp>(left, right)};
}

Expr operator*(const Expr &left, const Expr &right) {
  // Your code here.
  return {std::make_shared<MultiplyOp>(left, right)};
}

Expr operator/(const Expr &left, const Expr &right) {
  // Your code here.
  return {std::make_shared<DivideOp>(left, right)};
}

#endif // EXPR_HPPendif // EXPR_HPP
