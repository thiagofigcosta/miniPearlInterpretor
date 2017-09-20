#include "ForeachCommand.hpp"

#include <cassert>

ForeachCommand::ForeachCommand(ForeachHead* cond, Command* then, int line) 
    : Command(line),cond_(cond),then_(then){
}

ForeachCommand::~ForeachCommand() {
    delete cond_;
    delete then_;
}

void ForeachCommand::execute() {
    //TODO FIX ME
}
