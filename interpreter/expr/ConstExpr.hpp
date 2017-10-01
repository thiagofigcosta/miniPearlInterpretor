#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "Expr.hpp"

class ConstExpr : public Expr {
public:
    explicit ConstExpr(Value* value, int line);
    virtual ~ConstExpr();

    Value* expr();

private:
    Value* value_;

};

#endif
