#include "ListValue.hpp"

template<class T>
ListValue<T>::ListValue(int line) :
    CompositeValue(Value::List, line){
}

ListValue<T>::ListValue(std::list<PrimitiveValue<T>> l, int line) :
    CompositeValue(Value::List, line), list_value(l){
}

ListValue<T>::~ListValue() {
}

std::List<PrimitiveValue<T>> ListValue::value() {
    return list_value;
}
