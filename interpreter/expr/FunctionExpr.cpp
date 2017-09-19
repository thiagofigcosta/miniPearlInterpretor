#include "FunctionExpr.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

FunctionExpr::FunctionExpr(FunctionType type, Expr* param, int line) 
	: Expr(Expr::Function, line), type_(type), param_(param) {
}

FunctionExpr::~FunctionExpr() {
    if(param_)
    	delete param_;
}

//TODO fix showError message from syntacticalanalysis
Value* FunctionExpr::expr() {
	ListValue* lv;
	HashValue* hv;
	std::string in;
	PrimitiveValue<std::string>* pv;
	Value* paramVal=param_->expr();
	switch(type_){
		case Input:
			if(paramVal->type()==Value::String){
				StringValue* sv=(StringValue*)paramVal;
				std::cout<<sv->value();
			}else{
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			std::getline(std::cin,in);
			return new StringValue(in,line_);
		case Size:
			int size;
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				size=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=paramVal;
				size=hv->value().size();
			}else {
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(size,line_);
		case Sort:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				ListValue* sortedl=(ListValue*)lv->clone();
				std::sort(sortedl->value().begin(),sortedl->value().end(),PrimitiveValue<lv->VarType>::cmp);
				return sortedl;
			}else{
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Reverse:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				ListValue* reversel=(ListValue*)lv->clone();
				std::reverse(reversel->value().begin(),reversel->value().end());
				return reversel;
			}else{
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Keys:
			if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				std::map<std::string,PrimitiveValue<hv->VarType>> mk=hv->value();
				std::vector<std::string> lk;
				for(std::map<std::string,PrimitiveValue<hv->VarType>>::iterator it = mk.begin(); it != mk.end(); ++it) {
					lk.push_back(it->first);
				}
				return new ListValue(lk,line_);
				}else{
					//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Values:
			if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				std::map<std::string,PrimitiveValue<hv->VarType>> mv=hv->value();
				std::vector<PrimitiveValue<hv->VarType>> lp;
				for(std::map<std::string,PrimitiveValue<hv->VarType>>::iterator it = mv.begin(); it != mv.end(); ++it) {
					lp.push_back(it->second);
				}
				return new ListValue(lp,line_);
				}else{
					//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Empty:
			int empt;
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				empt=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				empt=hv->value().size();
			}else {
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(empt==0,line_);
		case Pop:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				pv=lv->value().back();
				lv->value().pop_back();
				return pv;
			}else{
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Shift:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				pv=lv->value().front();
				lv->value().pop_front();
				return pv;
			}else{
				//SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		//default: SyntacticalAnalysis::showError("Invalid operation on function expr",line_);break;
	}
    return nullptr;
}
