#include "HashValue.hpp"

template<class T>
HashValue::HashValue(int line) :
    CompositeValue(Value::Hash, line){
	typedef T VarType;
}

HashValue::HashValue(std::map<std::string,PrimitiveValue<std::string>> m,int line) :
    CompositeValue(Value::Hash, line),hash_value(m){
}

HashValue::~HashValue() {
}

std::map<std::string,PrimitiveValue<T>> HashValue::value() {
    return hash_value;
}
