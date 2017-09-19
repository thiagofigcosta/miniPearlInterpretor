#include "Value.hpp"
#include "IntegerValue.hpp"
#include "StringValue.hpp"

//TODO fix showError message from syntacticalanalysis
bool Value::cmp(Value *a, Value *b){
    if(a->type()==Value::String&&b->type()==Value::String){
        StringValue* As=(StringValue*)a;
        StringValue* Bs=(StringValue*)b;
        return As->value()<Bs->value();
    }else if(a->type()==Value::String&&b->type()==Value::String){
        IntegerValue* Ai=(IntegerValue*)a;
        IntegerValue* Bi=(IntegerValue*)b;
        return Ai->value()<Bi->value();
    }else{
        //EXCEPTION
    }
    return false;
}