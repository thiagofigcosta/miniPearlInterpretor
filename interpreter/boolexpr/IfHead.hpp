#ifndef IFHEAD_H
#define IFHEAD_H

#include "PostCondition.hpp"
#include "BoolExpr.hpp"

class IfHead : public PostCondition {
public:
    explicit IfHead(BoolExpr* expr, int line);
    virtual ~IfHead();

    bool expr();

private:
    BoolExpr* expr_;

};

#endif
