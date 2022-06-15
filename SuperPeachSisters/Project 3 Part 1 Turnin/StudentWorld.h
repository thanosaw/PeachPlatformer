#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

class Actor;
class Peach;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld();
    
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    bool canMove(int x, int y);
    void addActor(Actor* actor);

private:
    std::vector<Actor*> m_actors;
    Peach* m_peach;
    int m_nActors;
    
};

#endif // STUDENTWORLD_H_
