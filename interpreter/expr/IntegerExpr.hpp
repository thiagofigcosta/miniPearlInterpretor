#ifndef INTEGER_EXPR_H
#define INTEGER_EXPR_H

#include "Expr.hpp"

class IntegerExpr : public Expr {
public:
	enum IntegerOp{
		Add,
		Sub,
		Mul,
		Div,
		Mod
	};

    explicit IntegerExpr(Expr* left, IntegerOp op, Expr* right, int line);
    virtual ~IntegerExpr();

    Value* expr();

private:
    Expr* left_;
    Expr* right_;
    IntegerOp op_;

};

#endif
