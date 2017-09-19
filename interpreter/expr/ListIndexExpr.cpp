#include "ListIndexExpr.hpp"
#include "../value/ListValue.hpp"

ListIndexExpr::ListIndexExpr(Expr* base, Expr* index, int line)
	:IndexExpr(base,index,line){
}

ListIndexExpr::~ListIndexExpr() {
    if(base_)
    	delete base_;
    if(index_)
    	delete index_;
}
//TODO fix showError message from syntacticalanalysis
void ListIndexExpr::setValue(Value* value) {
	if(value->type()!=Value::Integer||value->type()!=Value::String){
		//SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	if(base_->type()!=Value::List||index_->type()!=Value::Integer){
		//SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	ListValue* lv=(ListValue*)base_->expr();
	IntegerValue* iv=(IntegerValue*)index_->expr();
	if(value->type()!=Value::Integer){
		StringValue* sattr=(StringValue*)value;
		lv->value()[iv->value()]=sattr;
	}else if(value->type()!=Value::String){
		IntegerValue* iattr=(IntegerValue*)value;
		lv->value()[iv->value()]=iattr;
	}
}

Value* ListIndexExpr::expr() {
	return base_->expr();
}