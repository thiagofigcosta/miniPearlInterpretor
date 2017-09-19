#ifndef HASHINDEXEXPR_H
#define HASHINDEXEXPR_H

#include "IndexExpr.hpp"
#include "../value/StringValue.hpp"
#include "../value/IntegerValue.hpp"

class HashIndexExpr : public IndexExpr {
public:
    explicit HashIndexExpr(Expr* base, Expr* index, int line);
    virtual ~HashIndexExpr();

    void setValue(Value* value);

private:

};

#endif
