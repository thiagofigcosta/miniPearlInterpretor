#ifndef PUSH_COMMAND_H
#define PUSH_COMMAND_H

#include "ActionCommand.hpp"
#include "../value/ListValue.hpp"
#include "../value/StringValue.hpp"
#include "../value/IntegerValue.hpp"

class Expr;

class PushCommand : public ActionCommand {
public:
    explicit PushCommand(Expr* list,Expr* values, int line);
    virtual ~PushCommand();

    virtual void execute();

private:
    Expr* list_;
    Expr* values_;

};

#endif
