#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "SetExpr.hpp"

class Variable : public SetExpr {
public:
    explicit Variable(std::string name);
    virtual ~Variable();

    virtual Value* expr();

    virtual void setValue(Value* value);

    std::string getName(){return name_;}
protected:
    std::string name_;

};

#endif
