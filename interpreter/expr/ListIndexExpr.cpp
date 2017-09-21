#include "ListIndexExpr.hpp"
#include "../value/ListValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

ListIndexExpr::ListIndexExpr(Expr* base, Expr* index, int line)
	:IndexExpr(base,index,line){
}

ListIndexExpr::~ListIndexExpr() {
    if(base_)
    	delete base_;
    if(index_)
    	delete index_;
}
void ListIndexExpr::setValue(Value* value) {
	if(value->type()!=Value::Integer&&value->type()!=Value::String){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::List||idexv->type()!=Value::Integer){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	ListValue* lv=(ListValue*)base_->expr();
	IntegerValue* iv=(IntegerValue*)index_->expr();
	if(value->type()==Value::String){
		StringValue* sattr=(StringValue*)value;
		lv->value()[iv->value()]=sattr;
		//TODO deveria ser apenas lv->value()[iv->value()]=sattr;
		Value* tmpV=lv->value()[iv->value()];
		if(tmpV->type()==Value::String){
			StringValue* tmpVS=(StringValue*)tmpV;
			tmpVS->setValue(sattr->value());
		}
	}else if(value->type()==Value::Integer){
		IntegerValue* iattr=(IntegerValue*)value;
		//TODO deveria ser apenas lv->value()[iv->value()]=iattr;
		Value* tmpV=lv->value()[iv->value()];
		if(tmpV->type()==Value::Integer){
			IntegerValue* tmpVI=(IntegerValue*)tmpV;
			tmpVI->setValue(iattr->value());
		}
	}
}

Value* ListIndexExpr::expr() {
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::List||idexv->type()!=Value::Integer){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	ListValue* lv=(ListValue*)base_->expr();
	IntegerValue* iv=(IntegerValue*)index_->expr();
	return lv->value()[iv->value()];
}