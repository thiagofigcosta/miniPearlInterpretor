#ifndef ASSINGCOMMAND_H
#define ASSINGCOMMAND_H

#include "Command.hpp"
#include "../boolexpr/PostCondition.hpp"

#include <list>

class PostConditionalCommand : public Command {
public:
    explicit PostConditionalCommand(Command* cmd,PostCondition* cond,int line);
    virtual ~PostConditionalCommand();

    void execute();

private:
    Command* cmd_;
    PostCondition* cond_;

};

#endif
