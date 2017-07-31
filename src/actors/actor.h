#ifndef JACKAL_ACTOR_H
#define JACKAL_ACTOR_H
#include "../board/subject.h"
#include "../board/tilegrid.h"
#include <string>

class Actor : public Subject{
    const std::string name;
    const char rep;
    const Color color;
    int x, y;
   
public:

   Actor(std::string name, char rep, Color color, int x=0, int y=0);

   // Accessors
   std::string getName() const;
   char getRep() const;
   Color getColor() const;
   int getX() const;
   int getY() const;


   // Mutators
   void setX(const int x);
   void setY(const int y);
   

};

#endif
