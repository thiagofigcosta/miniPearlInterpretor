#ifndef FOREACHHEAD_H
#define FOREACHHEAD_H

#include "PostCondition.hpp"
#include "../expr/Expr.hpp"
#include "../expr/Variable.hpp"

class ForeachHead : public PostCondition {
public:
    explicit ForeachHead(Variable* var,Expr* expr, int line);
    virtual ~ForeachHead();

    void reset();
    bool expr();

private:
    Expr* expr_;
    Variable* var_;

};

#endif
