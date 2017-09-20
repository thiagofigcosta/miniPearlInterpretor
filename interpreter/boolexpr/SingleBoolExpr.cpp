#include "SingleBoolExpr.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

SingleBoolExpr::SingleBoolExpr(Expr* left, SingleBoolExpr::RelOp op, Expr* right, int line) :
    BoolExpr(BoolExpr::SingleBoolExpr, line), left_(left), op_(op), right_(right) {
}

SingleBoolExpr::~SingleBoolExpr() {
    delete left_;
    delete right_;
}

bool SingleBoolExpr::expr() {
	switch(op_){
		case Equal:return left_->expr()==right_->expr();
        case NotEqual:return left_->expr()!=right_->expr();
        case LowerThan:return left_->expr()<right_->expr();
        case LowerEqual:return left_->expr()<=right_->expr();
        case GreaterThan:return left_->expr()>right_->expr();
        case GreaterEqual:return left_->expr()>=right_->expr();
        default: SyntacticalAnalysis::showError("Invalid operation on single bool expr",line_);break;
	}
    return false;
}
