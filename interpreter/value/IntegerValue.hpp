#ifndef INTEGER_VALUE_H
#define INTEGER_VALUE_H

#include "PrimitiveValue.hpp"

class IntegerValue : public PrimitiveValue<int> {
public:
    explicit IntegerValue(int intValue, int line);
    virtual ~IntegerValue();

    void setValue(int new_value){int_value=new_value;}

    virtual int value();

private:
    int int_value;

};

#endif
