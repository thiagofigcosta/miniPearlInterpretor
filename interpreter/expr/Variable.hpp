#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "SetExpr.hpp"

class Variable : public SetExpr {
public:
    explicit Variable(std::string name);
    virtual ~Variable(){}

    Value* expr(){return value_;}

    virtual void setValue(Value* value) = 0;

    std::string getName(){return name_;}
protected:
    std::string name_;

};

#endif
