#ifndef SCALAR_VARIABLE_H
#define SCALAR_VARIABLE_H

#include "Variable.hpp"
#include "../value/IntegerValue.hpp"

class ScalarVariable : public Variable {
public:
    explicit ScalarVariable(std::string name);
    virtual ~ScalarVariable();

    void setValue(Value* value);

private:

};

#endif
