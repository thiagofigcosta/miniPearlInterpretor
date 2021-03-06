#include "ListVariable.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

ListVariable::ListVariable(std::string name) : Variable(name) {
}

ListVariable::~ListVariable() {
    delete value_;
}

void ListVariable::setValue(Value* value) {
	if(value->type()!=Value::List){
		SyntacticalAnalysis::showError("Invalid type on set list var",line_);
	}
    value_=(ListValue*)value;
}
