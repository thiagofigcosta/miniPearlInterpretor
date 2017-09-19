#ifndef INTEGER_VALUE_H
#define INTEGER_VALUE_H

#include "PrimitiveValue.hpp"
#include "../value/IntegerValue.hpp"

class IntegerValue : public PrimitiveValue<int> {
public:
    explicit IntegerValue(int intValue, int line);
    virtual ~IntegerValue();

    virtual int value();

private:
    int int_value;

};

#endif
