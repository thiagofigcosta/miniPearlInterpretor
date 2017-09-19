#include "PrimitiveValue.hpp"
#include "IntegerValue.hpp"
#include "StringValue.hpp"

//TODO fix me
template<class T>
bool PrimitiveValue<T>::cmp(PrimitiveValue<T> const &a, PrimitiveValue<T> const &b){
    	Value* A=(Value*)a;
    	Value* B=(Value*)b;
    	if(A->type()==Value::String&&B->type()==Value::String){
    		StringValue* As=(StringValue*)A;
    		StringValue* Bs=(StringValue*)B;
    		return As->value()<Bs->value();
    	}else if(A->type()==Value::String&&B->type()==Value::String){
    		IntegerValue* Ai=(IntegerValue*)A;
    		IntegerValue* Bi=(IntegerValue*)B;
    		return Ai->value()<Bi->value();
    	}else{
    		//EXCEPTION
    	}
    	return false;
    }