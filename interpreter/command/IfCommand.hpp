#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "ConditionalCommand.hpp"

class IfCommand : public ConditionalCommand {
public:
    explicit IfCommand(BoolExpr* expr, Command* then, int line);
    explicit IfCommand(BoolExpr* expr, Command* then, Command* elsecmd, int line);
    virtual ~IfCommand();

    void execute();

private:
    Command* else_;

};

#endif
