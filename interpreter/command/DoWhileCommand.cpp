#include "DoWhileCommand.hpp"

#include <cassert>

DoWhileCommand::DoWhileCommand(BoolExpr* expr, Command* cmd, int line) 
    : ConditionalCommand(expr,cmd,line){
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
