#ifndef LIST_VALUE_H
#define LIST_VALUE_H

#include <vector>
#include <string>
#include "CompositeValue.hpp"
#include "PrimitiveValue.hpp"

template<class T>
class ListValue : public CompositeValue<std::vector<PrimitiveValue<T>>> {
public:
    explicit ListValue(int line);
    explicit ListValue(std::vector<PrimitiveValue<T>> l,int line);
    virtual ~ListValue();

    virtual std::vector<PrimitiveValue<T>> value();

private:
    std::vector<PrimitiveValue<T>> list_value;

};

#endif
