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
    NumExpression() : value(0) {}
    explicit NumExpression(long num) : value(num) {}
    virtual std::string toString() const {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    virtual ~NumExpression() {}
};

class PlusExpression : public Expression
{
    Expression *lhs;
    Expression *rhs;
public:
    PlusExpression() {}
    PlusExpression(Expression *lhs, Expression *rhs)
        : lhs(lhs), rhs(rhs) {}
    virtual std::string toString() const {
        std::stringstream ss;
        ss << '(' << lhs->toString() << " + " << rhs->toString() << ')';
        return ss.str();
    }
    virtual ~PlusExpression() {
        delete lhs;
        delete rhs;
    }
};
