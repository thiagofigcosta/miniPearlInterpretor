#ifndef HASHINDEXEXPR_H
#define HASHINDEXEXPR_H

#include "IndexExpr.hpp"
#include "../value/StringValue.hpp"
#include "../value/IntegerValue.hpp"

class ListIndexExpr : public IndexExpr {
public:
    explicit ListIndexExpr(Expr* base, Expr* index, int line);
    virtual ~ListIndexExpr();

    Value* expr();

    void setValue(Value* value);

private:

};

#endif
