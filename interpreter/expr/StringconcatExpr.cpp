#include "StringconcatExpr.hpp"
#include "FunctionExpr.hpp"
#include "../value/IntegerValue.hpp"
#include "../value/ListValue.hpp"
#include "../value/HashValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

StringconcatExpr::StringconcatExpr(Expr* left, Expr* right, int line)
	: Expr(Expr::Function, line), left_(left), right_(right) {
}

StringconcatExpr::~StringconcatExpr() {
	delete left_;
	delete right_;
}

Value* StringconcatExpr::expr() {
	if((left_->type()!=Expr::Const&&left_->type()!=Expr::Set&&left_->type()!=Expr::Function)||(right_->type()!=Expr::Set&&right_->type()!=Expr::Const&&right_->type()!=Expr::Function)){
		SyntacticalAnalysis::showError("Invalid type on string expr",line_);
	}
	std::string l="";
	std::string r="";
	Value* lv=left_->expr();
	Value* rv=right_->expr();
	if(lv->type()==Value::Integer){
		IntegerValue* liv=(IntegerValue*)left_->expr();
		l=Value::to_string(liv->value());
	}if(lv->type()==Value::Hash){
		HashValue* hv=(HashValue*)left_->expr();
        for(auto &vf:hv->value()){
            std::string s=vf.first;
            Value* v=vf.second;
            if(v->type()==Value::Integer){
                IntegerValue* iv=(IntegerValue*)v;
                l+=s+"=>"+Value::to_string(iv->value())+",";
            }else{
                StringValue* sv=(StringValue*)v;
                l+=s+"=>"+sv->value()+",";
            }
        }
        l.pop_back();
	}if(lv->type()==Value::List){
		ListValue* lv=(ListValue*)left_->expr();
        for(Value* v:lv->value()){
            if(v->type()==Value::Integer){
                IntegerValue* iv=(IntegerValue*)v;
                l+=Value::to_string(iv->value())+",";
            }else{
                StringValue* sv=(StringValue*)v;
                l+=sv->value()+",";
            }
        }
        l.pop_back();
	}else if(lv->type()==Value::String){
		StringValue* lsv=(StringValue*)left_->expr();
		l=lsv->value();
	}

	if(rv->type()==Value::Integer){
		IntegerValue* riv=(IntegerValue*)right_->expr();
		r=Value::to_string(riv->value());
	}else if(rv->type()==Value::Hash){
		HashValue* hv=(HashValue*)right_->expr();
        for(auto &vf:hv->value()){
            std::string s=vf.first;
            Value* v=vf.second;
            if(v->type()==Value::Integer){
                IntegerValue* iv=(IntegerValue*)v;
                r+=s+"=>"+Value::to_string(iv->value())+",";
            }else{
                StringValue* sv=(StringValue*)v;
                r+=s+"=>"+sv->value()+",";
            }
        }
        r.pop_back();
	}if(rv->type()==Value::List){
		ListValue* lv=(ListValue*)right_->expr();
        for(Value* v:lv->value()){
            if(v->type()==Value::Integer){
                IntegerValue* iv=(IntegerValue*)v;
                r+=Value::to_string(iv->value())+",";
            }else{
                StringValue* sv=(StringValue*)v;
                r+=sv->value()+",";
            }
        }
        r.pop_back();
	}else if(rv->type()==Value::String){
		StringValue* rsv=(StringValue*)right_->expr();
		r=rsv->value();
	}
	return new StringValue(l+r,line_);
}
