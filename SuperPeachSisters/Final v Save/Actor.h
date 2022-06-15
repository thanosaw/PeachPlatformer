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
    virtual bool isDead() const;
    virtual bool isSolid() =0;
    StudentWorld* getWorld() const;
    virtual void doSomething();
    virtual bool isKoopa(){
        return false;
    }
    virtual int getScoreIncrease(){
        return m_scoreIncrease;
    }
    virtual void setScoreIncrease(int x){
        m_scoreIncrease=x;
    }
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
    
    virtual bool isSolid(){
        return true;
    }
    virtual void bonk();
private:
    
};

class Peach : public Actor{
public:
    Peach(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool isSolid(){
        return false;
    }
    void canShoot(){
        m_shoot=true;
    }
    
    void gotMushroom(){
        
        m_jumpPower= true;
    }
    
    void gotStar(){
        m_star=true;
        m_invincible= true;
        m_InvTickCount=150;
    }
    bool hasStar(){
        return m_star;
    }
    bool hasMushroom(){
        return m_jumpPower;
    }
    bool hasFlower(){
        return m_shoot;
    }
    void setInvTickCount(int ticks);
    int getInvTickCount() const;
    bool isInvincible() const{
        return m_invincible;
    }
    
    void decHp(){
        m_hp--;
    }
    void hpUp(){
        m_hp = 2;
    }
    int getHp(){
        return m_hp;
    }
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
    virtual void doSomething();
    virtual bool isSolid(){
        return true;
    }
    
    
};
class InteractableObject : public Actor{
public:
    InteractableObject(bool holdsGoodie, int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    
    virtual bool isSolid(){
        return false;
    }
    
    bool hasGoodie(){
        return goody;
    }
    void useGoodie(){
        goody = false;
    }
    void initGoodie(){
        goody = true;
    }
private:
    bool goody;
};

class Flag : public InteractableObject {
public:
    Flag(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid(){
        return false;
    }
    virtual void bonk();
    virtual void doSomething();
    
    
};
class Mario : public InteractableObject {
public:
    Mario(bool holdsGoodie, int x, int y, StudentWorld* world);
    virtual bool isSolid(){
        return false;
    }
    virtual void bonk();
    virtual void doSomething();
    
    
};

class FlowerBlock : public InteractableObject{
public:
    FlowerBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    
    virtual bool isSolid(){
        return true;
    }
    
    
    virtual void bonk();
    
    
};
class MushroomBlock : public InteractableObject{
public:
    MushroomBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    
    virtual bool isSolid(){
        return true;
    }
    
    
    virtual void bonk();
    
    
};
class StarBlock : public InteractableObject{
public:
    StarBlock(bool holdsGoodie, int x, int y, StudentWorld* world);
    
    virtual bool isSolid(){
        return true;
    }
    
    virtual void bonk();
    
    
};

class PowerUp : public Actor{
public:
    PowerUp(int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    
    virtual bool isSolid(){
        return false;
    }
    
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
    
    virtual bool isSolid(){
        return false;
    }
    
    void doSomething();
    
    
};

class Goomba : public MovingEnemy{
public:
    Goomba(int x, int y, StudentWorld* world);
    
};

class Koopa : public MovingEnemy{
public:
    Koopa(int x, int y, StudentWorld* world);
    virtual bool isKoopa(){
        return true;
    }
};

class Pirahna : public Actor{
public:
    Pirahna(int x, int y, StudentWorld* world);
    virtual void doSomething();
    virtual bool isSolid(){
        return false;
    }
    
    void setFiringDelay(){
        m_firingDelay = 40;
    }
    void decFiringDelay(){
        m_firingDelay--;
    }
    int getFiringDelay(){
        return m_firingDelay;
    }
private:
    int m_firingDelay;
};

class MovingObject : public Actor{
public:
    MovingObject( int ID, int x, int y, int direction, int depth, double size, bool dead, bool takesDamage, StudentWorld* world) :
    Actor(ID,  x, y,direction, depth,  size, dead, takesDamage,  world){};
    virtual void doSomething();
    virtual bool isSolid(){
        return false;
    }
    bool isKillsPeach(){
        return killsPeach;
    }
    void setKillsPeach(bool var){
        killsPeach = var;
    }
    virtual bool isShell(){
        return false;
    }
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
    
    virtual bool isShell(){
        return true;
    }
    
};

#endif // ACTOR_H_


