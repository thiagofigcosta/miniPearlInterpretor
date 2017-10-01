#include "ForeachHead.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

ForeachHead::ForeachHead(Variable* var,Expr* expr, int line):
    PostCondition(line), var_(var),expr_(expr){
}

ForeachHead::~ForeachHead() {
    delete var_;
    delete expr_;
}

ListValue* ForeachHead::getList() {
	ListValue* lv=(ListValue*)expr_->expr();
    return lv;
}

Variable* ForeachHead::getVar(){
	return var_;
}

bool ForeachHead::expr() {
    return true;
}