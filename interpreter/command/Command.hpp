#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual ~Command() {}

    int line() const { return line_; }
    virtual void execute()=0;

protected:
    explicit Command(int line) : line_(line) {}
    int line_;

};

#endif
