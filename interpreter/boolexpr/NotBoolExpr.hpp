#ifndef NOTBOOLEXPR_H
#define NOTBOOLEXPR_H

#include "BoolExpr.hpp"

class NotBoolExpr : public BoolExpr {
public:
    explicit NotBoolExpr(BoolExpr* expr, int line);
    virtual ~NotBoolExpr();

    bool expr();

private:
    BoolExpr* bool_expr;

};

#endif
