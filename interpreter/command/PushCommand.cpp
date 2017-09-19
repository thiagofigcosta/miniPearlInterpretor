#include <iostream>
#include <cassert>

#include "PushCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"

PushCommand::PushCommand(Expr* list,Expr* values, int line)
    : ActionCommand(line), list_(list), values_(values) {
}

PushCommand::~PushCommand() {
    if (list_)
        delete list_;
    if (values_)
        delete values_;
}
//TODO fix me
void PushCommand::execute() {
    if (list_&&values_) {
        ListValue* l =(ListValue*)list_->expr();
        Value* value=values_->expr();
        if(value->type()==Value::String){
            StringValue* sv=(StringValue*)value;
            l->value().push_back(sv->value());
        }else if(value->type()==Value::Integer){
            IntegerValue* iv=(IntegerValue*)value;
            l->value().push_back(iv->value());
        }else{
            //SyntacticalAnalysis::showError("Invalid type on push cmd",line_);
        }
    }else{
        //SyntacticalAnalysis::showError("Invalid operation on push cmd",line_);
    }
}
