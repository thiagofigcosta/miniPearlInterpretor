#include "CompositeBoolExpr.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

CompositeBoolExpr::CompositeBoolExpr(BoolExpr* left, CompositeBoolExpr::BoolOp op, BoolExpr*right, int line) :
    BoolExpr(BoolExpr::CompositeBoolExpr, line), left_(left), op_(op), right_(right) {
}

CompositeBoolExpr::~CompositeBoolExpr() {
	delete left_;
	delete right_;
}

bool CompositeBoolExpr::expr() {
	switch(op_){
		case And:return left_->expr()&&right_->expr();
        case Or:return left_->expr()||right_->expr();
        default: SyntacticalAnalysis::showError("Invalid operation on composite bool expr",line_);break;
	}
    return false;
}
