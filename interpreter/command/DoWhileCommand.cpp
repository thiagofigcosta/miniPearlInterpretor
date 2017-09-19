#include "DoWhileCommand.hpp"

#include <cassert>

DoWhileCommand::DoWhileCommand(BoolExpr* expr, Command* cmd, int line) 
    : ConditionalCommand(line), expr_(expr), cmd_(cmd) {
}

DoWhileCommand::~DoWhileCommand() {
    delete expr_;
    delete cmd_;
}

void DoWhileCommand::execute() {
    do{
    	cmd_->execute();
    }while(expr_->expr());
}
