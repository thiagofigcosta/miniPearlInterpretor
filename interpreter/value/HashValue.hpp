#ifndef HASH_VALUE_H
#define HASH_VALUE_H

#include <map>
#include <string>
#include "CompositeValue.hpp"
#include "PrimitiveValue.hpp"

class HashValue : public CompositeValue<std::map<std::string,Value*> > {
public:
    explicit HashValue(int line);
    explicit HashValue(std::map<std::string,Value*> m,int line);
    virtual ~HashValue();

    virtual std::map<std::string,Value*> value();

private:
    std::map<std::string,Value*> hash_value;

};

#endif
