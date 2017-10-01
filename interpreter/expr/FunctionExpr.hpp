#ifndef FUNCTION_EXPR_H
#define FUNCTION_EXPR_H

#include "Expr.hpp"
#include "../value/ListValue.hpp"
#include "../value/HashValue.hpp"
#include "../value/IntegerValue.hpp"
#include "../value/StringValue.hpp"
#include "../value/PrimitiveValue.hpp"



class FunctionExpr : public Expr {
public:
	enum FunctionType{
		Input,
		Size,
		Sort,
		Reverse,
		Keys,
		Values,
		Empty,
		Pop,
		Shift
	};

    explicit FunctionExpr(FunctionType type, Expr* param, int line);
    virtual ~FunctionExpr();

    Value* expr();

private:
    Expr* param_;
    FunctionType type_;

};

#endif
