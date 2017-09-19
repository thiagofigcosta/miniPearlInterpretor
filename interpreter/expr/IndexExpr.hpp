#ifndef INDEXEXPR_H
#define INDEXEXPR_H

#include "SetExpr.hpp"

class IndexExpr : public SetExpr {
public:
    explicit IndexExpr(Expr* base, Expr* index, int line)
    :SetExpr(line),base_(base),index_(index){}
    virtual ~IndexExpr()=0;

    virtual Value* expr()=0;

    virtual void setValue(Value* value);

protected:
    Expr* base_;
    Expr* index_;

};

#endif
