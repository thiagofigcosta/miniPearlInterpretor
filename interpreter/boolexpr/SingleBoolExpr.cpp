#include "SingleBoolExpr.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"
#include "../value/IntegerValue.hpp"

SingleBoolExpr::SingleBoolExpr(Expr* left, SingleBoolExpr::RelOp op, Expr* right, int line) :
    BoolExpr(BoolExpr::SingleBoolExpr, line), left_(left), op_(op), right_(right) {
}

SingleBoolExpr::~SingleBoolExpr() {
    delete left_;
    delete right_;
}

bool SingleBoolExpr::expr(){
    IntegerValue* l=(IntegerValue*)left_->expr();
    IntegerValue* r=(IntegerValue*)right_->expr();
	switch(op_){
		case Equal:return l->value()==r->value();
        case NotEqual:return l->value()!=r->value();
        case LowerThan:return l->value()<r->value();
        case LowerEqual:return l->value()<=r->value();
        case GreaterThan:return l->value()>r->value();
        case GreaterEqual:return l->value()>=r->value();
        default: SyntacticalAnalysis::showError("Invalid operation on single bool expr",line_);break;
	}
    return false;
}
