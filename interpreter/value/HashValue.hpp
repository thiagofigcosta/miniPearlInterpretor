#ifndef HASH_VALUE_H
#define HASH_VALUE_H

#include <map>
#include <string>
#include "CompositeValue.hpp"
#include "PrimitiveValue.hpp"

template<class T>
class HashValue : public CompositeValue<std::map<std::string,PrimitiveValue<T>>> {
public:
    explicit HashValue(int line);
    explicit HashValue(std::map<std::string,PrimitiveValue<T>> m,int line);
    virtual ~HashValue();

    virtual std::map<std::string,PrimitiveValue<T>> value();

private:
    std::map<std::string,PrimitiveValue<T>> hash_value;

};

#endif
