#include "PostConditionalCommand.hpp"

#include <cassert>

PostConditionalCommand::PostConditionalCommand(Command* cmd,PostCondition* cond,int line) 
    : Command(line), cmd_(cmd), cond_(cond) {
}

PostConditionalCommand::~PostConditionalCommand() {
    delete cmd_;
    delete cond_;
}

void PostConditionalCommand::execute() {
    //TODO QUE QUE FAZ AQUI? (if que vai depois do comando)
}
