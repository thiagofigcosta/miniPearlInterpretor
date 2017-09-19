#include "ScalarVariable.hpp"

ScalarVariable::ScalarVariable(std::string name) : name_(name) {
}

ScalarVariable::~ScalarVariable() {
    delete value_;
}

void ScalarVariable::setValue(Value* value) {
	if(value->type()!=Value::Integer)
		SyntacticalAnalysis::showError("Invalid type on set scalar var",line_);
    value_=(IntegerValue*)value;
}
