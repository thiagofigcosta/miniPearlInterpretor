#ifndef COMMANDS_BLOCK_H
#define COMMANDS_BLOCK_H

#include "Command.hpp"

#include <list>

class CommandsBlock : public Command {
public:
    explicit CommandsBlock();
    virtual ~CommandsBlock();

    void addCommand(Command* c);

    void execute();

private:
    std::list<Command*> m_cmds;

};

#endif
