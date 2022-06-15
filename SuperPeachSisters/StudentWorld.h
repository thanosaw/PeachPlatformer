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
    void finishLevel();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    bool canMove(int x, int y, bool ground);
    void addActor(Actor* actor);
    bool overlap(Actor* a);
    bool overlap(Actor* a,Actor* b);
    void flowerPower();
    void addFlower(int x, int y);
    void mushroomPower();
    void addMushroom(int x, int y);
    void starPower();
    void addStar(int x, int y);
    void takeDamage(Actor* act);
    bool hasStar();
    void peachTakeDmg();
    bool hitEnemyActor(Actor* hitActor);
    bool pirahnaTargeting(int y);
    bool onRight(int x);
    bool inRange(int x);
    void gameWon();
    void addShell(int x, int y, int direction);
    bool overlapDamageable(Actor* me);
    
private:
    std::vector<Actor*> m_actors;
    Peach* m_peach;
    int m_nActors;
    bool m_levelComplete;
    bool m_gameWon;
};

#endif // STUDENTWORLD_H_
