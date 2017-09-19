#include "ListIndexExpr.hpp"
#include "../value/ListValue.hpp"

ListIndexExpr::ListIndexExpr(Expr* base, Expr* index, int line)
	:base_(base),index_(index),line_(line){
}

ListIndexExpr::~ListIndexExpr() {
    if(base_)
    	delete base_;
    if(index_)
    	delete index_;
}

void ListIndexExpr::setValue(Value* value) {
	if(value->type()!=Value::Integer||value->type()!=Value::String)
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	if(base_->type()!=Value::List||index_->type()!=Value::Integer)
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	ListValue* lv=base_->expr();
	IntegerValue* iv=index_->expr();
	if(value->type()!=Value::Integer){
		StringValue* sattr=(StringValue*)value;
		lv->value()[iv->value()]=sattr->value();
	}else if(value->type()!=Value::String){
		IntegerValue* iattr=(IntegerValue*)value;
		lv->value()[iv->value()]=iattr->value();
	}
}
