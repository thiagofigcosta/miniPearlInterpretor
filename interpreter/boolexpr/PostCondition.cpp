#include "PostCondition.hpp"

PostCondition::PostCondition(BoolExpr* expr, bool repeat,int line) :
    BoolExpr(BoolExpr::PostCondition, line), repeat_(repeat), bool_expr(expr) {
}

PostCondition::PostCondition(BoolExpr* expr, int line) :
    BoolExpr(BoolExpr::PostCondition, line), repeat_(false), bool_expr(expr) {
}

PostCondition::~PostCondition() {
	if(bool_expr)
		delete bool_expr;
}

bool PostCondition::expr() {
    return bool_expr->expr();
}

bool PostCondition::isRepeat() {
    return repeat_;
}
