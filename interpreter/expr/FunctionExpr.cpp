#include "FunctionExpr.hpp"
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <algorithm>

FunctionExpr::FunctionExpr(FunctionType type, Expr* param, int line) 
	: Expr(Expr::Function, line), type_(type), param_(param) {
}

FunctionExpr::~FunctionExpr() {
    if(param_)
    	delete param_;
}

Value* FunctionExpr::expr() {
	ListValue* lv;
	HashValue* hv;
	PrimitiveValue<T>* pv;
	Value* paramVal=param->expr();
	switch(type_){
		case Input:
			if(paramVal->type()==Value::String){
				StringValue* sv=paramVal;
				std::cout<<sv->value();
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			std::string in;
			std::getline(std::cin,in);
			return new StringValue(in,line_);
		case Size:
			int size;
			if(paramVal->type()==Value::List){
				lv=paramVal;
				size=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=paramVal;
				size=hv->value().size();
			}else {
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(size,line_);
		case Sort:
			if(paramVal->type()==Value::List){
				lv=paramVal;
				ListValue* sortedl=lv->clone();
				std::sort(sortedl->value().begin(),sortedl->value().end());
				rerturn sortedl;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Reverse:
			if(paramVal->type()==Value::List){
				lv=paramVal;
				ListValue* reversel=lv->clone();
				std::reverse(reversel->value().begin(),reversel->value().end());
				rerturn reversel;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Keys:
			if(paramVal->type()==Value::Hash){
				hv=paramVal;
				std::map<std::string,PrimitiveValue<T>> m=hv->value();
				std::list<std::string> l;
				for(std::map<std::string,PrimitiveValue<T>>::iterator it = m.begin(); it != m.end(); ++it) {
					l.push_back(it->first);
				}
				return new ListValue(l,line_);
				}else{
					SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Values:
			if(paramVal->type()==Value::Hash){
				hv=paramVal;
				std::map<std::string,PrimitiveValue<T>> m=hv->value();
				std::list<PrimitiveValue<T>> l;
				for(std::map<std::string,PrimitiveValue<T>>::iterator it = m.begin(); it != m.end(); ++it) {
					l.push_back(it->second);
				}
				return new ListValue(l,line_);
				}else{
					SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Empty:
			int empt;
			if(paramVal->type()==Value::List){
				lv=paramVal;
				empt=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=paramVal;
				empt=hv->value().size();
			}else {
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(empt==0,line_);
		case Pop:
			if(paramVal->type()==Value::List){
				lv=paramVal;
				pv=lv->value().back();
				lv->value().pop_back();
				return pv;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Shift:
			if(paramVal->type()==Value::List){
				lv=paramVal;
				pv=lv->value().front();
				lv->value().pop_front();
				return pv;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		default: SyntacticalAnalysis::showError("Invalid operation on function expr",line_);
	}
    return nullptr;
}
