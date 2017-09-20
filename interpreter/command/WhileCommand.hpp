#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H

#include "Command.hpp"
#include "../boolexpr/BoolExpr.hpp"

class WhileCommand : public Command {
public:
    explicit WhileCommand(BoolExpr* expr, Command* cmd, int line);
    virtual ~WhileCommand();

    void execute();

private:
	BoolExpr* expr_;
	Command* cmd_;
};

#endif
