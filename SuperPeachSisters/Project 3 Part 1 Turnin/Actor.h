#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world);
    bool willTakeDamage() const;
    bool isDead() const;
    StudentWorld* getWorld() const;
    virtual void doSomething();

private:

    bool m_dead;
    bool m_takesDamage;
    StudentWorld* m_world;
    
};
class Block : public Actor{
public:
    Block(int x, int y, StudentWorld* world);
    virtual void doSomething();

private:

};

class Peach : public Actor{
public:
    Peach(int x, int y, StudentWorld* world);
    virtual void doSomething();
 //   void bonk();
};
#endif // ACTOR_H_
