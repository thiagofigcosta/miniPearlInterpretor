#include "StringconcatExpr.hpp"
#include <iostream>

StringconcatExpr::StringconcatExpr(Expr* left, Expr* right, int line) 
	: Expr(Expr::Function, line), left_(left), right_(right) {
}

StringconcatExpr::~StringconcatExpr() {
	delete left_;
	delete right_;
}
//TODO fix me
Value* StringconcatExpr::expr() {
	if(left_->type()!=Expr::String||right_->type()!=Expr::String){
		//SyntacticalAnalysis::showError("Invalid type on string expr",line_);
	}
	StringValue* lv=(StringValue*)left_->expr();
	StringValue* rv=(StringValue*)right_->expr();
	std::string l=lv->value();
	std::string r=rv->value();
	return new StringValue(l+r,line_);
}
