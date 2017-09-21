#ifndef STRING_VALUE_H
#define STRING_VALUE_H

#include "PrimitiveValue.hpp"
#include <string>

class StringValue : public PrimitiveValue<std::string> {
public:
    explicit StringValue(std::string strValue, int line);
    virtual ~StringValue();

    void setValue(std::string new_value){str_value=new_value;}

    virtual std::string value();

private:
    std::string str_value;

};

#endif
