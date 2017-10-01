#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "Command.hpp"
#include "../boolexpr/IfHead.hpp"

class IfCommand : public Command {
public:
    explicit IfCommand(IfHead* cond, Command* then, int line);
    explicit IfCommand(IfHead* cond, Command* then, Command* elsecmd, int line);
    virtual ~IfCommand();

    void execute();

private:
	IfHead* cond_;
	Command* then_;
    Command* else_;

};

#endif
