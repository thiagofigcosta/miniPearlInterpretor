#include "HashValue.hpp"

template<class T>
HashValue<T>::HashValue(int line) :
    CompositeValue(Value::Hash, line){
}

HashValue<T>::HashValue(std::map<std::string,PrimitiveValue<T>> m,int line) :
    CompositeValue(Value::Hash, line),hash_value(m){
}

HashValue<T>::~HashValue() {
}

std::map<std::string,PrimitiveValue<T>> HashValue::value() {
    return hash_value;
}
