#include <iostream>
#include <cassert>

#include "UnshiftCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"

UnshiftCommand::UnshiftCommand(Expr* list,Expr* values, int line)
    : ActionCommand(line), list_(list), values_(values) {
}

UnshiftCommand::~UnshiftCommand() {
    delete list_;
    delete values_;
}
//TODO fix showError message from syntacticalanalysis
void UnshiftCommand::execute() {
    if (list_&&values_) {
        ListValue* l=(ListValue*)list_->expr();
        Value* value=values_->expr();
        if(value->type()==Value::String){
            StringValue* sv=(StringValue*) value;
            l->value().insert(l->value().begin(),sv);
        }else if(value->type()==Value::Integer){
            IntegerValue* iv=(IntegerValue*) value;
            l->value().insert(l->value().begin(),iv);
        }else{
            //SyntacticalAnalysis::showError("Invalid type on unshift cmd",line_);
        }
    }else{
        //SyntacticalAnalysis::showError("Invalid operation on unshift cmd",line_);
    }
}
