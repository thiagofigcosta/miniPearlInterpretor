#ifndef FOREACHCOMMAND_H
#define FOREACHCOMMAND_H

#include "Command.hpp"
#include "../boolexpr/ForeachHead.hpp"

class ForeachCommand : public Command {
public:
    explicit ForeachCommand(ForeachHead* cond, Command* then, int line);
    virtual ~ForeachCommand();

    void execute();

private:
	ForeachHead* cond_;
	Command* then_;

};

#endif
