#include "StringconcatExpr.hpp"
#include "FunctionExpr.hpp"
#include "../value/IntegerValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

StringconcatExpr::StringconcatExpr(Expr* left, Expr* right, int line) 
	: Expr(Expr::Function, line), left_(left), right_(right) {
}

StringconcatExpr::~StringconcatExpr() {
	delete left_;
	delete right_;
}
#include <iostream>
Value* StringconcatExpr::expr() {
	if((left_->type()!=Expr::Const&&left_->type()!=Expr::Set&&left_->type()!=Expr::Function)||(right_->type()!=Expr::Set&&right_->type()!=Expr::Const)){
		SyntacticalAnalysis::showError("Invalid type on string expr",line_);
	}
	std::string l;
	std::string r;
	Value* lv=left_->expr();
	Value* rv=right_->expr();
	if(lv->type()==Value::Integer){
		IntegerValue* liv=(IntegerValue*)left_->expr();
		l=std::to_string(liv->value());
	}else{
		StringValue* lsv=(StringValue*)left_->expr();
		l=lsv->value();
	}

	if(rv->type()==Value::Integer){
		IntegerValue* riv=(IntegerValue*)right_->expr();
		r=std::to_string(riv->value());
	}else{
		StringValue* rsv=(StringValue*)right_->expr();
		r=rsv->value();
		
	}
	return new StringValue(l+r,line_);
}