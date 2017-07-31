#ifndef JACKAL_SUBJECT_H
#define JACKAL_SUBJECT_H
#include <vector>

class Observer;

class Subject{
    
    std::vector<Observer *> observers;

public:

    virtual ~Subject() = 0;

    void attach(Observer *observer);

    void detach(Observer *observer);

    void notify();

};

#endif
