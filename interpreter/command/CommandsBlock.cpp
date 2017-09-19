#include "CommandsBlock.hpp"

#include <cassert>

CommandsBlock::CommandsBlock() : Command(-1) {
}

CommandsBlock::~CommandsBlock() {
    std::list<Command*>::iterator it, e;
    for (it = m_cmds.begin(), e = m_cmds.end(); it != e; it++) {
        delete *it;
    }
}

void CommandsBlock::addCommand(Command* c) {
    assert(c != 0);

    m_cmds.push_back(c);
}

void CommandsBlock::execute() {
    std::list<Command*>::iterator it, e;
    for (it = m_cmds.begin(), e = m_cmds.end(); it != e; it++) {
        Command* c = *it;
        c->execute();
    }
}
