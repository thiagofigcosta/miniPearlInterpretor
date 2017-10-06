#include "SingleBoolExpr.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"
#include "../value/IntegerValue.hpp"
#include "../value/StringValue.hpp"

SingleBoolExpr::SingleBoolExpr(Expr* left, SingleBoolExpr::RelOp op, Expr* right, int line) :
    BoolExpr(BoolExpr::SingleBoolExpr, line), left_(left), op_(op), right_(right) {
}

SingleBoolExpr::~SingleBoolExpr() {
    delete left_;
    delete right_;
}

bool SingleBoolExpr::expr(){
    Value* lv=(Value*)left_->expr();
    Value* rv=(Value*)right_->expr();
    IntegerValue* liv;
    IntegerValue* riv;
    StringValue* lsv;
    StringValue* rsv;
    int l=0,r=0;
    if(lv->type()==Value::Integer){
        liv=(IntegerValue*)lv;
        l=liv->value();
    }else if(lv->type()==Value::String){
        lsv=(StringValue*)lv;
        l=Value::to_int(lsv->value());
    }else{
        SyntacticalAnalysis::showError("Invalid type on single bool expr",line_);
    }
    if(rv->type()==Value::Integer){
        riv=(IntegerValue*)rv;
        r=riv->value();
    }else if(rv->type()==Value::String){
        rsv=(StringValue*)rv;
        r=Value::to_int(rsv->value());
    }else{
        SyntacticalAnalysis::showError("Invalid type on single bool expr",line_);
    }
	switch(op_){
		case Equal:return l==r;
        case NotEqual:return l!=r;
        case LowerThan:return l<r;
        case LowerEqual:return l<=r;
        case GreaterThan:return l>r;
        case GreaterEqual:return l>=r;
        default: SyntacticalAnalysis::showError("Invalid operation on single bool expr",line_);break;
	}
    return false;
}
