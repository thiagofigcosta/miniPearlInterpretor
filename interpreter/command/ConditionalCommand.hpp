#ifndef CONDITIONAL_COMMAND_H
#define CONDITIONAL_COMMAND_H

#include "Command.hpp"
#include "../boolexpr/BoolExpr.hpp"

class ConditionalCommand : public Command {
public:
    explicit ConditionalCommand(BoolExpr* expr, Command* cmd, int line) : 
    Command(line), expr_(expr),cmd_(cmd) {}
    virtual ~ConditionalCommand() {}

    virtual void execute() = 0;

protected:
	BoolExpr* expr_;
	Command* cmd_;

};

#endif
