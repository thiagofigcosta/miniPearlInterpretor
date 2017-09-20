#include "ForeachHead.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

ForeachHead::ForeachHead(Variable* var,Expr* expr, int line):
    PostCondition(line), var_(var),expr_(expr){
}

ForeachHead::~ForeachHead() {
    delete var_;
    delete expr_;
}

bool ForeachHead::expr() {
	//TODO fix me
    return false;
}

void ForeachHead::reset() {
	//TODO fix me
}