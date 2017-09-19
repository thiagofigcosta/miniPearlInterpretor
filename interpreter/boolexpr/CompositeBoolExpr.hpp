#ifndef COMPOSITEBOOLEXPR_H
#define COMPOSITEBOOLEXPR_H

#include "BoolExpr.hpp"

class CompositeBoolExpr : public BoolExpr {
public:
	enum BoolOp {
        And,
        Or,
    };

    explicit CompositeBoolExpr(BoolExpr left, CompositeBoolExpr::BoolOp op, BoolExpr right, int line);
    virtual ~CompositeBoolExpr();

    virtual bool expr();

private:
    BoolExpr* left_;
 BoolExpr* right_;
   	int op_;

};

#endif
