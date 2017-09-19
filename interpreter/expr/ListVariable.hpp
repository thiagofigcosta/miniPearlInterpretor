#ifndef LIST_VARIABLE_H
#define LIST_VARIABLE_H

#include "Variable.hpp"
#include "../value/ListValue.hpp"

class ListVariable : public Variable {
public:
    explicit ListVariable(std::string name);
    virtual ~ListVariable();

    void setValue(Value* value);

private:

};

#endif
