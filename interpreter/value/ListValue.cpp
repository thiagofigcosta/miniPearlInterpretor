#include "ListValue.hpp"

template<class T>
ListValue::ListValue(int line) :
    CompositeValue(Value::List, line){
	typedef T VarType;
}

ListValue::ListValue(std::vector<PrimitiveValue<T>> l, int line) :
    CompositeValue(Value::List, line), list_value(l){
}

ListValue::~ListValue() {
}

std::vector<PrimitiveValue<T>> ListValue::value() {
    return list_value;
}
