#include "IntegerExpr.hpp"
#include "../value/IntegerValue.hpp"
#include <iostream>

IntegerExpr::IntegerExpr(Expr* left, IntegerOp op, Expr* right, int line) 
	: Expr(Expr::Function, line), left_(left), op_(op),right_(right) {
}

IntegerExpr::~IntegerExpr() {
	delete left_;
	delete right_;
}

Value* IntegerExpr::expr() {
	if(left_->type()!=Expr::Integer||right_->type()!=Expr::Integer)
		SyntacticalAnalysis::showError("Invalid type on integer expr",line_);
	IntegerValue* lv=(IntegerValue*)left_->expr();
	IntegerValue* rv=(IntegerValue*)right_->expr();
	int l=lv->value();
	int r=rv->value();
	switch(op_){
		case Add:
			return new IntegerValue(l+r,line_);
		case Sub:
			return new IntegerValue(l-r,line_);
		case Mul:
			return new IntegerValue(l*r,line_);
		case Div:
			return new IntegerValue(l/r,line_);
		case Mod:
			return new IntegerValue(l%r,line_);
		default: SyntacticalAnalysis::showError("Invalid operation on integer expr",line_);
	}
    return nullptr;
}
