#include "Value.hpp"
#include "IntegerValue.hpp"
#include "StringValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"
#include <sstream>
#include <string>

bool Value::cmp(Value *a, Value *b){
    if(a->type()==Value::String&&b->type()==Value::String){
        StringValue* As=(StringValue*)a;
        StringValue* Bs=(StringValue*)b;
        return As->value()<Bs->value();
    }else if(a->type()==Value::Integer&&b->type()==Value::Integer){
        IntegerValue* Ai=(IntegerValue*)a;
        IntegerValue* Bi=(IntegerValue*)b;
        return Ai->value()<Bi->value();
    }else{
        SyntacticalAnalysis::showError("Invalid type("+Value::to_string(a->type())+","+Value::to_string(b->type())+") on for comparison",-1);
    }
    return false;
}

std::string Value::to_string(int v){
    std::ostringstream ss;
    ss << v;
    return ss.str();
}


int Value::to_int(std::string v){
     std::istringstream ss(v);
     int result;
     return ss >> result ? result : 0;
}
