#ifndef INDEXEXPR_Hitit
#define INDEXEXPR_H

#include "Expr.hpp"
#include "SetExpr.hpp"

class IndexExpr : public SetExpr {
public:
    explicit IndexExpr(Expr* base,Expr* index,int line):SetExpr(line),base_(base),index_(index){}
    virtual ~IndexExpr() {}

    virtual Value* expr()=0;

    virtual void setValue(Value* value)=0;

protected:
    Expr* base_;
    Expr* index_;

};

#endif
