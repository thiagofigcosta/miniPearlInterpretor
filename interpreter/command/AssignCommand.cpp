#include "AssignCommand.hpp"

#include <cassert>

AssignCommand::AssignCommand(SetExpr* lhs,Expr* rhs,int line) 
    : Command(line), lhs_(lhs), rhs_(rhs) {
}

AssignCommand::~AssignCommand() {
    delete rhs_;
    delete lhs_;
}	

void AssignCommand::execute() {
    lhs_->setValue(rhs_->expr());
}
