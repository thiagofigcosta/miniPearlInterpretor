#include "NotBoolExpr.hpp"

NotBoolExpr::NotBoolExpr(BoolExpr *expr, int line) :
    BoolExpr(BoolExpr::NotBoolExpr, line), bool_expr(expr) {
}

NotBoolExpr::~NotBoolExpr() {
	if(bool_expr)
		delete bool_expr;
}

bool NotBoolExpr::expr() {
    return bool_expr->expr();
}
