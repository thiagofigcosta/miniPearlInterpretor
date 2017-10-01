#include <iostream>
#include <algorithm>
#include <cassert>

#include "UnshiftCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

UnshiftCommand::UnshiftCommand(Expr* list,Expr* values, int line)
    : ActionCommand(line), list_(list), values_(values) {
}

UnshiftCommand::~UnshiftCommand() {
    delete list_;
    delete values_;
}

void UnshiftCommand::execute() {
    if (list_&&values_) {
        ListValue* l=(ListValue*)list_->expr();
        std::vector<Value*> valVec=l->value();
        Value* value=values_->expr();
        if(value->type()==Value::String){
            StringValue* sv=(StringValue*) value;
            valVec.insert(valVec.begin(),sv);
        }else if(value->type()==Value::Integer){
            IntegerValue* iv=(IntegerValue*) value;
            valVec.insert(valVec.begin(),iv);
        }else if(value->type()==Value::List){
            ListValue* lv=(ListValue*)value;
            std::vector<Value*> lvv=lv->value();
            valVec.insert(valVec.begin(),lvv.begin(),lvv.end());
        }else{
            SyntacticalAnalysis::showError("Invalid type on unshift cmd",line_);
        }
        l->setVec(valVec);
    }else{
        SyntacticalAnalysis::showError("Invalid operation on unshift cmd",line_);
    }
}
