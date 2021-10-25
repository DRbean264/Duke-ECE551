#include <iostream>
#include <cmath>
#include <sstream>

class Expression
{
public:
    virtual std::string toString() const = 0;
    virtual ~Expression() {}
};

class NumExpression : public Expression
{
    long value;
public:
    explicit NumExpression(long num) : value(num) {}
    virtual std::string toString() const {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    virtual ~NumExpression() {}
};

class BinaryExpression : public Expression {
    Expression *lhs;
    Expression *rhs;
public:
    BinaryExpression(Expression *lhs, Expression *rhs)
        : lhs(lhs), rhs(rhs) {}
    virtual std::string toString() const {
        std::stringstream ss;
        ss << '(' << lhs->toString() << ' ' << getOperator() << ' ' << rhs->toString() << ')';
        return ss.str();
    }
    virtual char getOperator() const = 0;
    virtual ~BinaryExpression() {
        delete lhs;
        delete rhs;
    }
};

class PlusExpression : public BinaryExpression
{
    static char op;
public:
    PlusExpression(Expression *lhs, Expression *rhs)
        : BinaryExpression(lhs, rhs) {}
    virtual char getOperator() const {
        return op;
    }
    virtual ~PlusExpression() {}
};

class MinusExpression : public BinaryExpression
{
    static char op;
public:
    MinusExpression(Expression *lhs, Expression *rhs)
        : BinaryExpression(lhs, rhs) {}
    virtual char getOperator() const {
        return op;
    }
    virtual ~MinusExpression() {}
};

class TimesExpression : public BinaryExpression
{
    static char op;
public:
    TimesExpression(Expression *lhs, Expression *rhs)
        : BinaryExpression(lhs, rhs) {}
    virtual char getOperator() const {
        return op;
    }
    virtual ~TimesExpression() {}
};

class DivExpression : public BinaryExpression
{
    static char op;
public:
    DivExpression(Expression *lhs, Expression *rhs)
        : BinaryExpression(lhs, rhs) {}
    virtual char getOperator() const {
        return op;
    }
    virtual ~DivExpression() {}
};

char PlusExpression::op = '+';
char MinusExpression::op = '-';
char TimesExpression::op = '*';
char DivExpression::op = '/';
