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

void UnshiftCommand::execute() {
    if (list_&&values_) {
        ListValue* l= list_->value();
        Value* value=values_->value();
        l->value().push_front(value->value());
    }else{
        SyntacticalAnalysis::showError("Invalid operation on unshift cmd",line_);
    }
}
