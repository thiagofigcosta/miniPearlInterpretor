#ifndef FOREACHHEAD_H
#define FOREACHHEAD_H

#include "PostCondition.hpp"
#include "../expr/Expr.hpp"
#include "../expr/Variable.hpp"
#include "../value/ListValue.hpp"

class ForeachHead : public PostCondition {
public:
    explicit ForeachHead(Variable* var,Expr* expr, int line);
    virtual ~ForeachHead();

    ListValue* getList();
    Variable* getVar();

private:
	bool expr();
    Expr* expr_;
    Variable* var_;

};

#endif
