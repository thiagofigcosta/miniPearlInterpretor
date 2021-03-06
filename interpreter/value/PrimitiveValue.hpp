#ifndef PRIMITIVE_VALUE_H
#define PRIMITIVE_VALUE_H

#include "Value.hpp"

template<class T>
class PrimitiveValue : public Value {
public:
    explicit PrimitiveValue(enum Value::Type type, int line) : Value(type, line) {}
    virtual ~PrimitiveValue() {}

    virtual T value()=0;
};

#endif
