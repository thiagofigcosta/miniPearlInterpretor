#ifndef HASH_VARIABLE_H
#define HASH_VARIABLE_H

#include "Variable.hpp"
#include "../value/HashValue.hpp"

class HashVariable : public Variable {
public:
    explicit HashVariable(std::string name);
    virtual ~HashVariable();

    void setValue(Value* value);

private:

};

#endif
