#ifndef COMPOSITE_VALUE_H
#define COMPOSITE_VALUE_H

#include "Value.hpp"

template<class T>
class CompositeValue : public Value {
public:
    explicit CompositeValue(enum Value::Type type, int line) : Value(type, line) {}
    virtual ~CompositeValue() {}

    virtual T value() = 0;
};

#endif
