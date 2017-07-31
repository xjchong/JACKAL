#ifndef JACKAL_OBSERVER_H
#define JACKAL_OBSERVER_H

class Subject;

class Observer{
public:

    virtual ~Observer(){}

    virtual void update(const Subject &subject) = 0;

};

#endif
