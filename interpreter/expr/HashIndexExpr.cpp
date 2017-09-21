#include "HashIndexExpr.hpp"
#include "../value/HashValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

HashIndexExpr::HashIndexExpr(Expr* base, Expr* index, int line)
	:IndexExpr(base,index,line){
}

HashIndexExpr::~HashIndexExpr() {
    if(base_)
    	delete base_;
    if(index_)
    	delete index_;
}

void HashIndexExpr::setValue(Value* value) {
	if(value->type()!=Value::Integer&&value->type()!=Value::String){
		SyntacticalAnalysis::showError("Invalid type on set hash var at idx",line_);
	}
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::Hash||idexv->type()!=Value::String){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	HashValue* hv=(HashValue*)base_->expr();
	StringValue* sv=(StringValue*)index_->expr();
	if(value->type()!=Value::Integer){
		StringValue* sattr=(StringValue*)value;
		hv->value()[sv->value()]=sattr;
	}else if(value->type()!=Value::String){
		IntegerValue* iattr=(IntegerValue*)value;
		hv->value()[sv->value()]=iattr;
	}
}

Value* HashIndexExpr::expr() {
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::Hash||idexv->type()!=Value::String){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	HashValue* hv=(HashValue*)base_->expr();
	StringValue* sv=(StringValue*)index_->expr();
	return hv->value()[sv->value()];
}