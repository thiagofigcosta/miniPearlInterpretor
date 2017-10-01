#include "HashVariable.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

HashVariable::HashVariable(std::string name) : Variable(name) {
}

HashVariable::~HashVariable() {
    delete value_;
}

void HashVariable::setValue(Value* value) {
	if(value->type()!=Value::Hash){
		SyntacticalAnalysis::showError("Invalid type on set hash var",line_);
	}
    value_=(HashValue*)value;
}
