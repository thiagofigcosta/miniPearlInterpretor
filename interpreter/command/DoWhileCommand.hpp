#ifndef DOWHILECOMMAND_H
#define DOWHILECOMMAND_H

#include "Command.hpp"
#include "../boolexpr/BoolExpr.hpp"

class DoWhileCommand : public Command {
public:
    explicit DoWhileCommand(BoolExpr* expr, Command* cmd, int line);
    virtual ~DoWhileCommand();

    void execute();

private:
	BoolExpr* expr_;
	Command* cmd_;
};

#endif
