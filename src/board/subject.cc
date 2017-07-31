#include "observer.h"
#include "subject.h"
#include <algorithm>
using namespace std;


Subject::~Subject(){
    for (auto observer : observers) detach(observer);
}


void Subject::attach(Observer *observer){
    observers.emplace_back(observer);
}


void Subject::detach(Observer *observer){
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}


void Subject::notify(){
    for (auto observer : observers) observer->update(*this);
}
