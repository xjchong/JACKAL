#include "actor.h"
using namespace std;


Actor::Actor(string name, char rep, int x, int y)
    : name{name}, rep{rep}, x{x}, y{y}
{}


string Actor::getName() const { return name; }

char Actor::getRep() const { return rep; }

int Actor::getX() const { return x; }

int Actor::getY() const { return y; }


void Actor::setX(const int x){ this->x = x; }

void Actor::setY(const int y){ this->y = y; }
