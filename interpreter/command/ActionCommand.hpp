#ifndef ACTION_COMMAND_H
#define ACTION_COMMAND_H

#include "Command.hpp"

class ActionCommand : public Command {
public:
    explicit ActionCommand(int line) : Command(line) {}
    virtual ~ActionCommand() {}

    virtual void execute() = 0;
};

#endif
