#ifndef SET_EXPR_H
#define SET_EXPR_H

#include "Expr.hpp"

class SetExpr : public Expr {
public:
    explicit SetExpr(int line):Expr(Expr::Set,line),value_(nullptr){}
    virtual ~SetExpr(){}

    virtual Value* expr()=0;

	virtual void setValue(Value* value)=0;
protected:
    Value* value_;

};

#endif
