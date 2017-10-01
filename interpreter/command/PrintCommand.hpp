#ifndef PRINT_COMMAND_H
#define PRINT_COMMAND_H

#include "ActionCommand.hpp"

class Expr;

class PrintCommand : public ActionCommand {
public:
    explicit PrintCommand(Expr* expr, int line);
    explicit PrintCommand(bool newLine, int line);
    explicit PrintCommand(Expr* expr, bool newLine, int line);
    virtual ~PrintCommand();

    virtual void execute();

private:
    Expr* expr_;
    bool newLine_;

};

#endif
