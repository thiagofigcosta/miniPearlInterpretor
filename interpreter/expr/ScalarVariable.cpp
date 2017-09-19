#include "ScalarVariable.hpp"

ScalarVariable::ScalarVariable(std::string name) : Variable(name) {
}

ScalarVariable::~ScalarVariable() {
    delete value_;
}
//TODO fix showError message from syntacticalanalysis
void ScalarVariable::setValue(Value* value) {
	if(value->type()==Value::Integer){
		value_=(IntegerValue*)value;
	}else if(value->type()==Value::String){
		value_=(StringValue*)value;
	}else{
		//SyntacticalAnalysis::showError("Invalid type on set scalar var",line_);
	}
    
}
