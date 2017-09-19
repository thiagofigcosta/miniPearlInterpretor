#include "HashValue.hpp"

HashValue::HashValue(int line) :
    CompositeValue(Value::Hash, line){
}

HashValue::HashValue(std::map<std::string,Value*> m,int line) :
    CompositeValue(Value::Hash, line),hash_value(m){
}

HashValue::~HashValue() {
}

std::map<std::string,Value*> HashValue::value() {
    return hash_value;
}
