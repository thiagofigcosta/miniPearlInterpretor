#include "ListValue.hpp"

ListValue::ListValue(int line) :
    CompositeValue(Value::List, line){
}

ListValue::ListValue(std::vector<Value*> l, int line) :
    CompositeValue(Value::List, line), list_value(l){
}

ListValue::~ListValue() {
}

std::vector<Value*> ListValue::value() {
    return list_value;
}
