#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
// Class Structure
/*
Class Hierarchy:
GraphObject
    Actor
        Peach
 
        Block
 
        Pipe
 
        Pirahna
 
        Interactable Object
            Flag
            Mario
            FlowerBlock
            MushroomBlock
            StarBlock
 
        PowerUp
            Flower
            Mushroom
            Star
 
        MovingEnemy
            Goomba
            Koopa
        
        MovingObject
            PeachFireball
            PirahnaFireball
            Shell
*/
class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world);
    bool isDamageable() const;
    bool isDead() const;
    virtual bool isSolid() =0;
    StudentWorld* getWorld() const;
    virtual void doSomething();
    virtual bool isKoopa();
    virtual int getScoreIncrease();
    void setScoreIncrease(int x);
    virtual void bonk();
    void setDead();
private:
    int m_scoreIncrease;
    bool m_dead;
    bool m_takesDamage;
    StudentWorld* m_world;
};
class Block : public Actor{
public:
    Block(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool isSolid();
    virtual void bonk();
};

class Peach : public Actor{
public:
    Peach(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool isSolid();
    void canShoot();
    void gotMushroom();
    void gotStar();
    bool hasStar();
    bool hasMushroom();
    bool hasFlower();
    void setInvTickCount(int ticks);
    int getInvTickCount() const;
    bool isInvincible() const;
    void decHp();
    void hpUp();
    int getHp() const;
    void losePower();
private:
    int m_hp;
    int time_to_recharge_before_next_fire;
    int m_InvTickCount;
    bool m_shoot;
    bool m_invincible;
    bool m_star;
    bool m_jumpPower;
    int remaining_jump_power;
    //   void bonk();
};
class Pipe : public Actor{
public:
    Pipe(int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
};
class InteractableObject : public Actor{
public:
    InteractableObject(bool holdsGoodie, int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    bool hasGoodie();
    void useGoodie();
    void initGoodie();
private:
    bool goody;
};

class Flag : public InteractableObject {
public:
    Flag(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
    virtual void doSomething();

};
class Mario : public InteractableObject {
public:
    Mario(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
    virtual void doSomething();
};

class FlowerBlock : public InteractableObject{
public:
    FlowerBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
};
class MushroomBlock : public InteractableObject{
public:
    MushroomBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
};
class StarBlock : public InteractableObject{
public:
    StarBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid();
    virtual void bonk();
};

class PowerUp : public Actor{
public:
    PowerUp(int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    virtual bool isSolid();
    void doSomething();
private:
    virtual void powerUp()=0;
};

class Flower : public PowerUp{
public:
    Flower(int x, int y, StudentWorld* world);
private:
    virtual void powerUp();
};

class Mushroom : public PowerUp{
public:
    Mushroom(int x, int y, StudentWorld* world);
private:
    virtual void powerUp();
};

class Star : public PowerUp{
public:
    Star(int x, int y, StudentWorld* world);
private:
    virtual void powerUp();
};

class MovingEnemy : public Actor{
public:
    MovingEnemy(int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    virtual bool isSolid();
    void doSomething();
};

class Goomba : public MovingEnemy{
public:
    Goomba(int x, int y, StudentWorld* world);
};

class Koopa : public MovingEnemy{
public:
    Koopa(int x, int y, StudentWorld* world);
    virtual bool isKoopa();
};

class Pirahna : public Actor{
public:
    Pirahna(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool isSolid();
    void setFiringDelay();
    void decFiringDelay();
    int getFiringDelay();
private:
    int m_firingDelay;
};

class MovingObject : public Actor{
public:
    MovingObject( int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    virtual void doSomething();
    virtual bool isSolid();
    bool isKillsPeach();
    void setKillsPeach(bool var);
    virtual bool isShell();
private:
    bool killsPeach;
    
};
class PeachFireball : public MovingObject{
public:
    PeachFireball(int direction, int x, int y, StudentWorld* world);
};

class PirahnaFireball : public MovingObject{
public:
    PirahnaFireball(int direction, int x, int y, StudentWorld* world);
};

class Shell : public MovingObject{
public:
    Shell(int direction, int x, int y, StudentWorld* world);
    virtual bool isShell();
};

#endif // ACTOR_H_


