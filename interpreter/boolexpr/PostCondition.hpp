#ifndef POSTCONDITION_H
#define POSTCONDITION_H

#include "BoolExpr.hpp"

class PostCondition : public BoolExpr {
public:
    explicit PostCondition(int line):BoolExpr(BoolExpr::PostCondition,line){}
    virtual ~PostCondition(){}

    virtual bool expr()=0;
private:

};

#endif
