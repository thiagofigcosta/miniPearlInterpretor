#include "FunctionExpr.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "../../syntactical/SyntacticalAnalysis.hpp"

FunctionExpr::FunctionExpr(FunctionType type, Expr* param, int line)
	: Expr(Expr::Function, line), type_(type), param_(param) {
}

FunctionExpr::~FunctionExpr() {
    if(param_)
    	delete param_;
}

Value* FunctionExpr::expr(){
	ListValue* lv;
	HashValue* hv;
	StringValue* sv;
	IntegerValue* iv;
	std::string in;
	Value* val;
	std::vector<Value*> valVec;
	bool isNumber=true;
	Value* paramVal=param_->expr();
	switch(type_){
		case Input:
			if(paramVal->type()==Value::String){
				sv=(StringValue*)paramVal;
				std::cout<<sv->value()<<" ";
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			std::getline(std::cin,in);
			for(char c:in)
				if((c<'0'||c>'9')&&(c!='-')){
					isNumber=false;
					break;
				}
			if(isNumber&&in!="")
				return new IntegerValue(Value::to_int(in),line_);
			else
			    return new StringValue(in,line_);
		case Size:
			int size;
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				size=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				size=hv->value().size();
			}else {
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(size,line_);
		case Sort:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				valVec=lv->value();
				std::sort(valVec.begin(),valVec.end(),Value::cmp);
				return new ListValue(valVec,line_);
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Reverse:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				valVec=lv->value();
				std::reverse(valVec.begin(),valVec.end());
				return new ListValue(valVec,line_);
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Keys:
			if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				std::map<std::string,Value*> mk=hv->value();
				std::vector<Value*> lk;
				for(std::map<std::string,Value*>::iterator it = mk.begin(); it != mk.end(); ++it) {
					lk.push_back(new StringValue(it->first,line_));
				}
				return new ListValue(lk,line_);
				}else{
					SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Values:
			if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				std::map<std::string,Value*> mv=hv->value();
				std::vector<Value*> lp;
				for(std::map<std::string,Value*>::iterator it = mv.begin(); it != mv.end(); ++it) {
					lp.push_back(it->second);
				}
				return new ListValue(lp,line_);
				}else{
					SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
				}
			break;
		case Empty:
			int sz;
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				sz=lv->value().size();
			}else if(paramVal->type()==Value::Hash){
				hv=(HashValue*)paramVal;
				sz=hv->value().size();
			}else if(paramVal->type()==Value::String){
				sv=(StringValue*)paramVal;
				if(sv->value()=="")
					sz=0;
				else
					sz=1;
			}else if(paramVal->type()==Value::Integer){
					sz=0;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			return new IntegerValue(sz==0,line_);
		case Pop:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				valVec=lv->value();
				if(valVec.size()>0){
					val=valVec.back();
					valVec.pop_back();
					lv->setVec(valVec);
				}else
					val=0;
				return val;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		case Shift:
			if(paramVal->type()==Value::List){
				lv=(ListValue*)paramVal;
				valVec=lv->value();
				if(valVec.size()>0){
					val=valVec[0];
					valVec.erase(valVec.begin());
					lv->setVec(valVec);
				}else
					val=0;
				return val;
			}else{
				SyntacticalAnalysis::showError("Invalid value type on function expr",line_);
			}
			break;
		default: SyntacticalAnalysis::showError("Invalid operation on function expr",line_);break;
	}
    return nullptr;
}
