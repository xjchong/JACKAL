#ifndef JACKAL_COMMAND_H
#define JACKAL_COMMAND_H

class Actor;

class Command{

public:

    virtual ~Command(){}
    virtual void execute(Actor &actor) = 0;
};

#endif
