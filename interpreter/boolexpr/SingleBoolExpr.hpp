#ifndef SINGLEBOOLEXPR_H
#define SINGLEBOOLEXPR_H

#include "BoolExpr.hpp"
#include "../expr/Expr.hpp"

class SingleBoolExpr : public BoolExpr {
public:
	enum RelOp {
        Equal,
        NotEqual,
        LowerThan,
        LowerEqual,
        GreaterThan,
        GreaterEqual
    };

    explicit SingleBoolExpr(Expr* left, SingleBoolExpr::RelOp op, Expr* right, int line);
    virtual ~SingleBoolExpr();

    bool expr();

private:
    Expr* left_;
    Expr* right_;
   	int op_;

};

#endif
