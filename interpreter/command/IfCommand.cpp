#include "IfCommand.hpp"

#include <cassert>

IfCommand::IfCommand(BoolExpr* expr, Command* then, int line) 
    : ConditionalCommand(line), expr_(expr), cmd_(then) {
}

IfCommand::IfCommand(BoolExpr* expr, Command* then, Command* elsecmd,int line) 
    : ConditionalCommand(line), expr_(expr), cmd_(then), else_(elsecmd) {
}

IfCommand::~IfCommand() {
    delete expr_;
    delete cmd_;
    delete else_;
}

void IfCommand::execute() {
    if(expr_->expr()){
    	cmd_->execute();
    }else if(else_){
    	else_->execute();
    }
}
