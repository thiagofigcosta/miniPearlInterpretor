#include "ListIndexExpr.hpp"
#include "../value/ListValue.hpp"
#include "../expr/SetExpr.hpp"
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
    std::vector<Value*> vecVal;
	if(value->type()!=Value::Integer&&value->type()!=Value::String){
		SyntacticalAnalysis::showError("Invalid type on set list var at idx",line_);
	}
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::List||idexv->type()!=Value::Integer){
		SyntacticalAnalysis::showError("Invalid vec on set list var at idx",line_);
	}
	ListValue* lv=(ListValue*)base_->expr();
	IntegerValue* iv=(IntegerValue*)index_->expr();
    vecVal=lv->value();
    vecVal[iv->value()]=value;
    lv->setVec(vecVal);
}

Value* ListIndexExpr::expr() {
	Value* basev=(Value*)base_->expr();
	Value* idexv=(Value*)index_->expr();
	if(basev->type()!=Value::List||idexv->type()!=Value::Integer){
		SyntacticalAnalysis::showError("Invalid vec on get list var at idx",line_);
	}
	ListValue* lv=(ListValue*)base_->expr();
	IntegerValue* iv=(IntegerValue*)index_->expr();
	return lv->value()[iv->value()];
}
