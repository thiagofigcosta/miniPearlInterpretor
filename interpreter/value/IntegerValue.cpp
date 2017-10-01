#include "IntegerValue.hpp"

IntegerValue::IntegerValue(int intValue, int line) :
    PrimitiveValue(Value::Integer, line), int_value(intValue) {
}

IntegerValue::~IntegerValue() {
}

int IntegerValue::value() {
    return int_value;
}
