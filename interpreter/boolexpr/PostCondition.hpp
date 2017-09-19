#ifndef POSTCONDITION_H
#define POSTCONDITION_H

#include "BoolExpr.hpp"

class PostCondition : public BoolExpr {
public:
    explicit PostCondition(BoolExpr* expr, int line);
    explicit PostCondition(BoolExpr* expr, bool repeat,int line);
    virtual ~PostCondition();

    bool isRepeat();
    bool expr();

private:
    BoolExpr* bool_expr;
    bool repeat_;
};

#endif
