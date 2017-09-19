#ifndef LIST_VALUE_H
#define LIST_VALUE_H

#include <list>
#include "CompositeValue.hpp"
#include "PrimitiveValue.hpp"

template<class T>
class ListValue : public CompositeValue<std::list<PrimitiveValue<T>>> {
public:
    explicit ListValue(int line);
    explicit ListValue(std::list<PrimitiveValue<T>> l,int line);
    virtual ~ListValue();

    virtual std::list<PrimitiveValue<T>> value();

private:
    std::list<PrimitiveValue<T>> list_value;

};

#endif
