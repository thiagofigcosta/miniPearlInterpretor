#include "IfCommand.hpp"

#include <cassert>

IfCommand::IfCommand(IfHead* cond, Command* then, int line)
    : Command(line),cond_(cond),then_(then),else_(nullptr){
}

IfCommand::IfCommand(IfHead* cond, Command* then, Command* elsecmd,int line)
    : Command(line),cond_(cond),then_(then),else_(elsecmd) {
}

IfCommand::~IfCommand() {
    delete cond_;
    delete then_;
    delete else_;
}

void IfCommand::execute() {
    if(cond_->expr()){
    	then_->execute();
    }else if(else_){
    	else_->execute();
    }
}
