#include "IntegerExpr.hpp"
#include "../value/IntegerValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"
#include <iostream>

IntegerExpr::IntegerExpr(Expr* left, IntegerOp op, Expr* right, int line) 
	: Expr(Expr::Function, line), left_(left), op_(op),right_(right) {
}

IntegerExpr::~IntegerExpr() {
	delete left_;
	delete right_;
}
Value* IntegerExpr::expr(){
	Value* ltv=(Value*)left_->expr();
	Value* rtv=(Value*)right_->expr();
	if((ltv->type()!=Expr::Integer&&left_->type()!=Expr::Const&&left_->type()!=Expr::Function&&left_->type()!=Expr::Set)||(rtv->type()!=Expr::Integer&&right_->type()!=Expr::Const&&right_->type()!=Expr::Function&&right_->type()!=Expr::Set)){
		SyntacticalAnalysis::showError("Invalid type on integer expr",line_);
	}
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
		default: SyntacticalAnalysis::showError("Invalid operation on integer expr",line_);break;
	}
    return nullptr;
}
