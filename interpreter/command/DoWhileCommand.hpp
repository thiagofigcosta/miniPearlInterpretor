#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H

#include "ConditionalCommand.hpp"

class DoWhileCommand : public ConditionalCommand {
public:
    explicit DoWhileCommand(BoolExpr* expr, Command* cmd, int line);
    virtual ~DoWhileCommand();

    void execute();

private:

};

#endif
