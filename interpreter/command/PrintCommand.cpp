#include <iostream>
#include <cassert>

#include "PrintCommand.hpp"
#include "../expr/Expr.hpp"
#include "../value/IntegerValue.hpp"
#include "../value/StringValue.hpp"
#include "../value/HashValue.hpp"
#include "../value/ListValue.hpp"
#include "../../syntactical/SyntacticalAnalysis.hpp"

PrintCommand::PrintCommand(Expr* expr, int line)
    : ActionCommand(line), expr_(expr), newLine_(false) {
}

PrintCommand::PrintCommand(bool newLine, int line)
    : ActionCommand(line), expr_(0), newLine_(newLine) {
}

PrintCommand::PrintCommand(Expr* expr, bool newLine, int line)
    : ActionCommand(line), expr_(expr), newLine_(newLine) {
}

PrintCommand::~PrintCommand() {
    delete expr_;
}

void PrintCommand::execute() {
    if (expr_){
        std::string out="";
        Value* value=expr_->expr();
        StringValue* sv;
        IntegerValue* iv;
        HashValue* hv;
        ListValue* lv;
        assert(value!=nullptr);
        switch (value->type()) {
            case Value::Integer:
                iv=(IntegerValue*)value;
                std::cout<<iv->value();
                break;
            case Value::String:
                sv=(StringValue*)value;
                std::cout<<sv->value();
                break;
            case Value::List:
                lv=(ListValue*)value;
                for(Value* v:lv->value()){
                    if(v->type()==Value::Integer){
                        iv=(IntegerValue*)v;
                        out+=std::to_string(iv->value())+",";
                    }else{
                        sv=(StringValue*)v;
                        out+=sv->value()+",";
                    }
                }
                out.pop_back();
                std::cout<<out;
                break;
            case Value::Hash:
                hv=(HashValue*)value;
                for(auto &vf:hv->value()){
                    std::string s=vf.first;
                    Value* v=vf.second;
                    if(v->type()==Value::Integer){
                        iv=(IntegerValue*)v;
                        out+=s+"=>"+std::to_string(iv->value())+",";
                    }else{
                        sv=(StringValue*)v;
                        out+=s+"=>"+sv->value()+",";
                    }
                }
                out.pop_back();
                std::cout<<out;
                break;
            default:SyntacticalAnalysis::showError("Invalid operation on print cmd",line_);break;
        }
    }
    if (newLine_)
        std::cout<<std::endl;
}
