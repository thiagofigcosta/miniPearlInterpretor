#include "StringValue.hpp"

StringValue::StringValue(std::string strValue, int line) :
    PrimitiveValue(Value::String, line), str_value(strValue) {
}

StringValue::~StringValue() {
}

std::string StringValue::value() {
	return str_value;
}
