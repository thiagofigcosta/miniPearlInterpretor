#include "ForeachCommand.hpp"
#include "../expr/SetExpr.hpp"
#include "../value/ListValue.hpp"
#include <cassert>

ForeachCommand::ForeachCommand(ForeachHead* cond, Command* then, int line) 
    : Command(line),cond_(cond),then_(then){
}

ForeachCommand::~ForeachCommand() {
    delete cond_;
    delete then_;
}

void ForeachCommand::execute() {
    SetExpr* se=(SetExpr*)cond_->getVar();
    ListValue* lv=cond_->getList();
    for(Value* v:lv->value()){
    	se->setValue(v);
    	then_->execute();
    }
}
