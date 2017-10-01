#include <iostream>
#include <cassert>

#include "PushCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

PushCommand::PushCommand(Expr* list,Expr* values, int line)
    : ActionCommand(line), list_(list), values_(values) {
}

PushCommand::~PushCommand() {
    if (list_)
        delete list_;
    if (values_)
        delete values_;
}

void PushCommand::execute() {
    if (list_&&values_) {
        ListValue* l =(ListValue*)list_->expr();
        std::vector<Value*> valVec=l->value();
        Value* value=values_->expr();
        if(value->type()==Value::String){
            StringValue* sv=(StringValue*)value;
            valVec.push_back(sv);
        }else if(value->type()==Value::Integer){
            IntegerValue* iv=(IntegerValue*)value;
            valVec.push_back(iv);
        }else if(value->type()==Value::List){
            ListValue* lv=(ListValue*)value;
            std::vector<Value*> lvv=lv->value();
            valVec.insert(valVec.end(),lvv.begin(),lvv.end());
        }else{
            SyntacticalAnalysis::showError("Invalid type on push cmd",line_);
        }
        l->setVec(valVec);
    }else{
        SyntacticalAnalysis::showError("Invalid operation on push cmd",line_);
    }
}
