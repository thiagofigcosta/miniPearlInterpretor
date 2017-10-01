#ifndef STRINGCONCATEXPR_H
#define STRINGCONCATEXPR_H

#include "Expr.hpp"
#include "../value/StringValue.hpp"

class StringconcatExpr : public Expr {
public:
    explicit StringconcatExpr(Expr* left, Expr* right, int line);
    virtual ~StringconcatExpr();

    Value* expr();

private:
    Expr* left_;
    Expr* right_;

};

#endif
