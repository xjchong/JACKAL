#ifndef JACKAL_SUBJECT_H
#define JACKAL_SUBJECT_H
#include <vector>
#include <string>

class Observer;

class Subject{
    
    std::vector<Observer *> observers;

public:

    virtual ~Subject() = 0;

    void attach(Observer *observer);

    void detach(Observer *observer);

    void notify(std::string event = "");

};

#endif
