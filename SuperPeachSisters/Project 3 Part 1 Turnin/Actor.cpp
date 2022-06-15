#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
// Actor implementation
Actor::Actor(int ID, int startX, int startY, int direction, int depth, double size, bool alive, bool takesDamage, StudentWorld* world) : GraphObject(ID, startX, startY, direction, size, depth)
{

    m_dead = false;
    m_world = world;
    m_takesDamage = takesDamage;
}
void Actor::doSomething(){
    
}
bool Actor::willTakeDamage()const{
    return m_takesDamage;
}
bool Actor::isDead() const {
    return m_dead;
}
StudentWorld* Actor::getWorld() const{
    return m_world;
}
Block::Block(int x, int y, StudentWorld* world) :
Actor(IID_BLOCK, x, y, 0, 1, 2, false, false, world){
}
void Block::doSomething(){
    if (isDead()){
        return;
    }
    
}


Peach::Peach(int x, int y, StudentWorld* world) :
Actor(IID_PEACH, x, y, 0, 0, 1.0, false, true, world){}


void Peach::doSomething(){
    if (isDead())
        return;
    int input;
    if (getWorld()->getKey(input)){
        switch(input){
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getX()-4>=0&&getWorld()->canMove(getX()-4,getY())){
                    moveTo(getX()-4,getY());
                    break;
                }
                else
                break;
                
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if (getX()+4<VIEW_WIDTH&&getWorld()->canMove(getX()+4,getY())){
                    moveTo(getX()+4,getY());
                    break;
                }
                else
                break;
        }
                
        
    }
    
}
