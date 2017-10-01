#include "IfHead.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

IfHead::IfHead(BoolExpr* expr, int line):
    PostCondition(line), expr_(expr){
}

IfHead::~IfHead() {
    delete expr_;
}

bool IfHead::expr() {
    return expr_->expr();
}