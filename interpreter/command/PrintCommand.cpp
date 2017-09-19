#include <iostream>
#include <cassert>

#include "PrintCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"
#include "../value/StringValue.hpp"

PrintCommand::PrintCommand(Expr* expr, int line)
    : ActionCommand(line), expr_(expr), newLine_(false) {
}

PrintCommand::PrintCommand(bool newLine, int line)
    : ActionCommand(line), expr_(0), newLine_(newLine) {
}

PrintCommand::PrintCommand(Expr* expr, bool newLine, int line)
    : ActionCommand(line), expr_(expr), newLine_(newLine) {
}

PrintCommand::~PrintCommand() {
    delete expr_;
}
//TODO fix me
void PrintCommand::execute() {
    if (expr_) {
        Value* value = expr_->expr();
        StringValue* sv;
        IntegerValue* iv;
        assert(value != 0);

        switch (value->type()) {
            case Value::Integer:
                iv = (IntegerValue*) value;
                std::cout << iv->value();
                break;
            case Value::String:
                sv = (StringValue*) value;
                std::cout << sv->value();
                break;
/*
            case Value::List:
                // FIXME: Implement me!
                break;
            case Value::Hash:
                // FIXME: Implement me!
                break;
*/
           // default:SyntacticalAnalysis::showError("Invalid operation on print cmd",line_);break;
        }
    }

    if (newLine_)
        std::cout << std::endl;
}
