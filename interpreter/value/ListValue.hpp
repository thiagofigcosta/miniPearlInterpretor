#ifndef LIST_VALUE_H
#define LIST_VALUE_H

#include <vector>
#include <string>
#include "CompositeValue.hpp"
#include "PrimitiveValue.hpp"

class ListValue : public CompositeValue<std::vector<Value*> > {
public:
    explicit ListValue(int line);
    explicit ListValue(std::vector<Value*> l,int line);
    virtual ~ListValue();

    virtual std::vector<Value*> value();

private:
    std::vector<Value*> list_value;

};

#endif
