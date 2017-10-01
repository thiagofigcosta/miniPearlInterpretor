#ifndef UNSHIFT_COMMAND_H
#define UNSHIFT_COMMAND_H

#include "ActionCommand.hpp"
#include "../value/ListValue.hpp"
#include "../value/StringValue.hpp"
#include "../value/IntegerValue.hpp"

class Expr;

class UnshiftCommand : public ActionCommand {
public:
    explicit UnshiftCommand(Expr* list,Expr* values, int line);
    virtual ~UnshiftCommand();

    virtual void execute();

private:
    Expr* list_;
    Expr* values_;

};

#endif
