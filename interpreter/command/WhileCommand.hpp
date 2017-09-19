#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H

#include "ConditionalCommand.hpp"

class WhileCommand : public ConditionalCommand {
public:
    explicit WhileCommand(BoolExpr* expr, Command* cmd, int line);
    virtual ~WhileCommand();

    void execute();

private:

};

#endif
