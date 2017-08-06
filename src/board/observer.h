#ifndef JACKAL_OBSERVER_H
#define JACKAL_OBSERVER_H
#include <string>

class Subject;

class Observer{
public:

    virtual ~Observer(){}

    virtual void update(Subject &subject, std::string event) = 0;

};

#endif
