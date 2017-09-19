#ifndef EXPR_H
#define EXPR_H
    
#include "../value/Value.hpp"
class SyntacticalAnalysis;

class Expr {
public:
    enum Type {
        Const,
        Set,
        Function,
        Integer,
        String
    };

    virtual ~Expr() {}

    Expr::Type type() const { return type_; }
    int line() const { return line_; }

    virtual Value* expr() = 0;

protected:
    explicit Expr(Expr::Type type, int line) : type_(type), line_(line) {}
    Expr::Type type_;
    int line_;

};

#endif
