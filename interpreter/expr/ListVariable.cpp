#include "ListVariable.hpp"

ListVariable::ListVariable(std::string name) : Variable(name) {
}

ListVariable::~ListVariable() {
    delete value_;
}
//TODO fix showError message from syntacticalanalysis
void ListVariable::setValue(Value* value) {
	if(value->type()!=Value::List){
		//SyntacticalAnalysis::showError("Invalid type on set list var",line_);
	}
    value_=(ListValue*)value;
}
