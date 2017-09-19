#ifndef SET_EXPR_H
#define SET_EXPR_H

#include "Expr.hpp"

class SetExpr : public Expr {
public:
    explicit SetExpr(int line);
    virtual ~SetExpr();

    virtual Value* expr();

	virtual void setValue(Value* value);
protected:
    Value* value_;

};

#endif
