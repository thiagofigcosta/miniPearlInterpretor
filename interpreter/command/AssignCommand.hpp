#ifndef ASSINGCOMMAND_H
#define ASSINGCOMMAND_H

#include "Command.hpp"
#include "../expr/Expr.hpp"
#include "../expr/SetExpr.hpp"

#include <list>

class AssignCommand : public Command {
public:
    explicit AssignCommand(SetExpr* lhs,Expr* rhs,int line);
    virtual ~AssignCommand();

    void execute();

private:
    SetExpr* lhs_;
    Expr* rhs_;

};

#endif
