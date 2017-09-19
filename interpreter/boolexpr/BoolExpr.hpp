#ifndef BOOLEXPR_H
#define BOOLEXPR_H

class BoolExpr {
public:
    enum Type {
        NotBoolExpr,
        PostCondition,
        CompositeBoolExpr,
        SingleBoolExpr,
    };

    virtual ~BoolExpr();
    bool expr();
    BoolExpr::Type type() const { return type_; }
    int line() const { return type_; }

protected:
    explicit BoolExpr(BoolExpr::Type type, int line) : type_(type), line_(line) {}
    BoolExpr::Type type_;
    int line_;

};

#endif
