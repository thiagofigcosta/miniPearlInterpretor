#include "HashIndexExpr.hpp"
#include "../value/HashValue.hpp"

HashIndexExpr::HashIndexExpr(Expr* base, Expr* index, int line)
	:base_(base),index_(index),line_(line){
}

HashIndexExpr::~HashIndexExpr() {
    if(base_)
    	delete base_;
    if(index_)
    	delete index_;
}

void HashIndexExpr::setValue(Value* value) {
	if(value->type()!=Value::Integer||value->type()!=Value::String)
		SyntacticalAnalysis::showError("Invalid type on set hash var at idx",line_);
	if(base_->type()!=Value::Hash||index_->type()!=Value::String)
		SyntacticalAnalysis::showError("Invalid type on set hash var at idx",line_);
	HashValue* hv=base_->expr();
	StringValue* sv=index_->expr();
	if(value->type()!=Value::Integer){
		StringValue* sattr=(StringValue*)value;
		hv->value()[sv->value()]=sattr->value();
	}else if(value->type()!=Value::String){
		IntegerValue* iattr=(IntegerValue*)value;
		hv->value()[sv->value()]=iattr->value();
	}
}
