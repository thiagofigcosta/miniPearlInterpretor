#include "WhileCommand.hpp"

#include <cassert>

WhileCommand::WhileCommand(BoolExpr* expr, Command* cmd, int line) 
    : Command(line),expr_(expr),cmd_(cmd){
}

WhileCommand::~WhileCommand() {
    if(expr_)
        delete expr_;
    if(cmd_)
        delete cmd_;
}

void WhileCommand::execute() {
    while(expr_->expr()){
    	cmd_->execute();
    }
}
