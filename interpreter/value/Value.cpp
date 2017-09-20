#include "Value.hpp"
#include "IntegerValue.hpp"
#include "StringValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

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
        SyntacticalAnalysis::showError("Invalid type on for comparison",-1);
    }
    return false;
}