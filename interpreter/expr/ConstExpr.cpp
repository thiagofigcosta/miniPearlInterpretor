#include "ConstExpr.hpp"

ConstExpr::ConstExpr(Value* value, int line) : Expr(Expr::Const, line), value_(value) {
}

ConstExpr::~ConstExpr() {
    delete value_;
}

Value* ConstExpr::expr() {
    return value_;
}
