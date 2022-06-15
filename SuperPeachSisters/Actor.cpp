#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <iostream>
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
// Actor implementation
/**
 Constructor for Actor that initializes a few extra variables that keep track of whether or not it can take damage
 */
Actor::Actor(int ID, int startX, int startY, int direction, int depth, double size, bool alive, bool takesDamage, StudentWorld* world) : GraphObject(ID, startX, startY, direction, depth, size)
{
    
    m_dead = false;
    m_world = world;
    m_takesDamage = takesDamage;
}
void Actor::bonk(){
    
}
 bool Actor::isKoopa(){
    return false;
}
int Actor::getScoreIncrease(){
    return m_scoreIncrease;
}
void Actor::setScoreIncrease(int x){
    m_scoreIncrease=x;
}
/**
 setDead has specific behavior for when the actor is a Koopa, will add a shell in its place
 */
void Actor::setDead(){
    if (isKoopa()){
        
        getWorld()->addActor(new Shell(getDirection(),getX(),getY(), getWorld()));
        //cout << "was koopa" << endl;
    }
    m_dead=true;
}
void Actor::doSomething(){

   
}
bool Actor::isDamageable()const{
    return m_takesDamage;
}

bool Actor::isDead() const {
    return m_dead;
}

StudentWorld* Actor::getWorld() const{
    return m_world;
}
Block::Block(int x, int y, StudentWorld* world) :
Actor(IID_BLOCK, x, y, 0, 2, 1, false, false, world){
}
void Block::doSomething(){
    if (isDead()){
        return;
    }
    
}
void Block::bonk(){
    getWorld()->playSound(SOUND_PLAYER_BONK);
    //cout<< "bonked block" << endl;
}
bool Block::isSolid(){
    return true;
}
 bool Peach::isSolid(){
    return false;
}
void Peach::canShoot(){
    m_shoot=true;
}

void Peach::gotMushroom(){
    
    m_jumpPower= true;
}

void Peach::gotStar(){
    m_star=true;
    m_invincible= true;
    m_InvTickCount=150;
}
bool Peach::hasStar(){
    return m_star;
}

bool Peach::hasMushroom(){
    return m_jumpPower;
}
bool Peach::hasFlower(){
    return m_shoot;
}
bool Peach::isInvincible() const{
    return m_invincible;
}

void Peach::decHp(){
    m_hp--;
}
void Peach::hpUp(){
    m_hp = 2;
}
int Peach::getHp() const{
    return m_hp;
}
/**
 Initializes Peach's member variables to the default
 */
Peach::Peach(int x, int y, StudentWorld* world) :
Actor(IID_PEACH, x, y, 0, 0, 1.0, false, true, world){
    m_invincible = false;
    remaining_jump_power=0;
    m_shoot=false;
    time_to_recharge_before_next_fire =0;
    m_hp=1;
    m_star=false;
    m_InvTickCount=0;
    m_jumpPower=false;
}

void Peach::setInvTickCount(int ticks){
    m_invincible=true;
    m_InvTickCount = ticks;
}
int Peach::getInvTickCount() const{
    return m_InvTickCount;
}

void Peach::losePower(){
    
    m_jumpPower=false;
    m_shoot=false;
}
/**
 Everything peach does in a tick, shoot, move, die, all covered in this one function
 */
void Peach::doSomething(){
    
    //Check if dead
    //jump height implemented
    //invincibility
    //implement hp
    
    if (getHp()<=0){
        getWorld()->playSound(SOUND_PLAYER_DIE);
        setDead();
    }
    //    cout << getHp() << endl;
    if (isDead())
        return;
    //    cout << getY() << endl;
    if (m_InvTickCount<=0){
        m_invincible=false;
        m_star=false;
    }
    if (m_invincible&&m_InvTickCount>0){
        
        m_InvTickCount--;
    }
    else{
        m_invincible=false;
    }
    if (time_to_recharge_before_next_fire >0){
        time_to_recharge_before_next_fire--;
    }
    
    int input;
    if (remaining_jump_power>0){
        if (getWorld()->canMove(getX(), getY()+4, false)){
            moveTo(getX(), getY()+4);
            
        }
        else{
            //getWorld()->playSound(SOUND_PLAYER_BONK);
            remaining_jump_power=0;
        }
        remaining_jump_power = remaining_jump_power-1;
    }
    else{
        if (getWorld()->canMove(getX(), getY()-3, true)){
            moveTo(getX(), getY()-4);

        }

    }
    if (getWorld()->getKey(input)){
        switch(input){
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getX()-4>=0&&getWorld()->canMove(getX()-4,getY(), false)){
                    moveTo(getX()-4,getY());
                    
                    break;
                }
                else
                    break;
                
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if (getX()+4<VIEW_WIDTH&&getWorld()->canMove(getX()+4,getY(), false)){
                    moveTo(getX()+4,getY());
                    
                    break;
                }
                else
                    break;
            case KEY_PRESS_UP:
                
                if (!getWorld()->canMove(getX(),getY()-1, true)){
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                    int jHeight = 8;
                    if (m_jumpPower){
                        jHeight=12;
                    }
                    remaining_jump_power = jHeight;
                }
                break;
            case KEY_PRESS_SPACE:
                if (!m_shoot||time_to_recharge_before_next_fire >0){
                    
                    break;
                }
                else if (time_to_recharge_before_next_fire<=0){
                    time_to_recharge_before_next_fire =8;
                    
                    if (getDirection()==0){
                        
                        getWorld()->addActor(new PeachFireball(getDirection(),getX()+4,getY(),getWorld()));
                    }
                    else{
                        getWorld()->addActor(new PeachFireball(getDirection(),getX()-4,getY(),getWorld()));
                    }
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    break;
                }
                
                
        }
        
        
    }
    
    
}

Pipe::Pipe(int x, int y, StudentWorld* world) :
Actor(IID_PIPE, x, y, 0, 2, 1, false, false, world){
}
void Pipe::bonk(){
    getWorld()->playSound(SOUND_PLAYER_BONK);
}
bool Pipe::isSolid(){
    return true;
}
bool InteractableObject::hasGoodie(){
    return goody;
}
void InteractableObject::useGoodie(){
    goody = false;
}
void InteractableObject::initGoodie(){
    goody = true;
}
Flag::Flag(bool holdsGoodie, int x, int y, StudentWorld* world) :
InteractableObject(false, IID_FLAG, x, y, 0, 1, 1, false, false, world){
}
void Flag::bonk(){
    setScoreIncrease(1000);
    
    return;
    
}
bool Flag::isSolid(){
    return false;
}
/**
 Checks if Peach overlaps and moves on to the next level if so
 */
void Flag::doSomething(){
    if (isDead()){
        return;
    }
    if(getWorld()->overlap(this)&&!isDead()){
        //cout << "on flag" << endl;
        getWorld()->increaseScore(1000);
        setDead();
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->finishLevel();
    }
    
}
Mario::Mario(bool holdsGoodie, int x, int y, StudentWorld* world) :
InteractableObject(false, IID_MARIO, x, y, 0, 1, 1, false, false, world){
}
void Mario::bonk(){
    setScoreIncrease(1000);
    
    return;
    
}
bool Mario::isSolid(){
    return false;
}
/**
 Checks if Peach overlaps and ends the game if so
 */
void Mario::doSomething(){
    if (isDead()){
        return;
    }
    if(getWorld()->overlap(this)&&!isDead()){
        //cout << "on flag" << endl;
        getWorld()->increaseScore(1000);
        setDead();
        getWorld()->playSound(SOUND_GAME_OVER);
        getWorld()->gameWon();
    }
    
}
FlowerBlock::FlowerBlock(bool holdsGoodie, int x, int y, StudentWorld* world) :
InteractableObject(true, IID_BLOCK, x, y, 0, 2, 1, false, false, world){
    initGoodie();
}

bool FlowerBlock::isSolid(){
    return true;
}

void FlowerBlock::bonk(){
    if (hasGoodie()){
        getWorld()->addFlower(getX(),getY()+8);
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        //cout << "release Flower" << endl;
        useGoodie();
    }
    else{
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}
MushroomBlock::MushroomBlock(bool holdsGoodie, int x, int y, StudentWorld* world) :
InteractableObject(true, IID_BLOCK, x, y, 0, 2, 1, false, false, world){
    initGoodie();
}

bool MushroomBlock::isSolid(){
    return true;
}

void MushroomBlock::bonk(){
    if (hasGoodie()){
        getWorld()->addMushroom(getX(), getY()+8);
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        //cout << "release Mushroom" << endl;
        useGoodie();
    }
    else{
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}
StarBlock::StarBlock(bool holdsGoodie, int x, int y, StudentWorld* world) :
InteractableObject(true, IID_BLOCK, x, y, 0, 2, 1, false, false, world){
    initGoodie();
}

bool StarBlock::isSolid(){
    return true;
}

void StarBlock::bonk(){
    if (hasGoodie()){
        getWorld()->addStar(getX(),getY()+8);
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        //cout << "release Star" << endl;
        useGoodie();
    }
    else{
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
}
bool PowerUp::isSolid(){
    return false;
}
/**
 Checks if the powerup overlaps with Peach and moves it from side to side with falling
 */
void PowerUp::doSomething(){
    if (isDead()){
        return;
    }
    if(getWorld()->overlap(this)&&!isDead()){
        getWorld()->increaseScore(getScoreIncrease());
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        setDead();
        powerUp();
    }
    if (getWorld()->canMove(getX(),getY()-2,true)){
        moveTo(getX(),getY()-2);
    }
    if (getDirection()==0&&getWorld()->canMove(getX()+2,getY(),true)){
        moveTo(getX()+2,getY());
    }
    else if (getDirection()==180&&getWorld()->canMove(getX()-2,getY(),true)){
        moveTo(getX()-2,getY());
    }
    else{
        if (getDirection()==0){
            setDirection(180);
        }
        else{
            setDirection(0);
        }
    }
}
Flower::Flower(int x, int y, StudentWorld* world):
PowerUp(IID_FLOWER, x, y, 0, 1, 1, false, false, world){
    setScoreIncrease(50);
}

void Flower::powerUp(){
    //cout << "Got Flower!!" << endl;
    getWorld()->flowerPower();
    return;
}
Mushroom::Mushroom(int x, int y, StudentWorld* world):
PowerUp(IID_MUSHROOM, x, y, 0, 1, 1, false, false, world){
    setScoreIncrease(75);
}

void Mushroom::powerUp(){
    //cout << "Got mushroom!!" << endl;
    getWorld()->mushroomPower();
    return;
}

Star::Star(int x, int y, StudentWorld* world):
PowerUp(IID_STAR, x, y, 0, 1, 1, false, false, world){
    setScoreIncrease(100);
}

void Star::powerUp(){
    //cout << "Got star!!" << endl;
    getWorld()->starPower();
    return;
}
 bool MovingEnemy::isSolid(){
    return false;
}
/**
 Walks back and forth as an enemy should and checks if Peach overlaps with them
 */
void MovingEnemy::doSomething(){
    
    
    if (isDead()){
        
        // cout << "YA BOI DIED" << endl;
        return;
    }
    if(getWorld()->overlap(this)&&!isDead()){
        //cout << "OMG U DIED!!!" << endl;
        if (getWorld()->hasStar()){
            getWorld()->playSound(SOUND_PLAYER_KICK);

            setDead();
            return;
        }
        getWorld()->peachTakeDmg();
        return;
    }
    
    if (getDirection()==0&&getWorld()->canMove(getX()+SPRITE_WIDTH,getY()-2,true)){
        setDirection(180);
    }
    else if (getDirection()==180&&getWorld()->canMove(getX()-SPRITE_WIDTH,getY()-2,true)){
        setDirection(0);
    }
    
    if (getDirection()==0&&getWorld()->canMove(getX()+1,getY(),true)){
        moveTo(getX()+1,getY());
    }
    else if (getDirection()==180&&getWorld()->canMove(getX()-1,getY(),true)){
        moveTo(getX()-1,getY());
    }
    else{
        if (getDirection()==0){
            setDirection(180);
            moveTo(getX()-1,getY());
        }
        else{
            setDirection(0);
            moveTo(getX()+1,getY());
        }
    }
}
/**
 Set random direction to face
 */
Goomba::Goomba(int x, int y, StudentWorld* world):
MovingEnemy(IID_GOOMBA, x, y, 0, 1, 0, false, true, world){
    setScoreIncrease(100);
    int randDir = rand() %2;
    
    if (randDir==0){
        setDirection(0);
    }
    else{
        setDirection(180);
    }
    
}
bool Koopa::isKoopa(){
    return true;
}
Koopa::Koopa(int x, int y, StudentWorld* world):
MovingEnemy(IID_KOOPA, x, y, 0, 1, 0, false, true, world){
    setScoreIncrease(100);
    int randDir = rand() %2;
    
    if (randDir==1){
        setDirection(0);
    }
    else{
        setDirection(180);
    }
    
}
bool Pirahna::isSolid(){
    return false;
}

void Pirahna::setFiringDelay(){
    m_firingDelay = 40;
}
void Pirahna::decFiringDelay(){
    m_firingDelay--;
}
int Pirahna::getFiringDelay(){
    return m_firingDelay;
}
Pirahna::Pirahna(int x, int y, StudentWorld* world) :
Actor(IID_PIRANHA, x, y, 0, 1, 0, false, true, world){
    setScoreIncrease(1000);
    int randDir = rand() %3 +1;
    
    if (randDir==1){
        setDirection(0);
    }
    else{
        setDirection(180);
    }
    m_firingDelay =0;
}
/**
 Checks if Peach is in range and fires at her if so, also turns to face her if she is in Pirahnas line of sight
 */
void Pirahna::doSomething(){
    increaseAnimationNumber();
    if (isDead()){
        
        
        return;
    }
    if(getWorld()->overlap(this)&&!isDead()){
        
        if (getWorld()->hasStar()){
            
            getWorld()->playSound(SOUND_PLAYER_KICK);
            setDead();
            return;
        }
        getWorld()->peachTakeDmg();
        return;
    }
    if (getWorld()->pirahnaTargeting(getY())){
        if (getWorld()->onRight(getX())){
            setDirection(0);
            
            if (getFiringDelay()>0){
                decFiringDelay();
            }
            else if (getWorld()->inRange(getX())){
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                getWorld()->addActor(new PirahnaFireball(0,getX(),getY(), getWorld()));
                
                setFiringDelay();
            }
            //check if firing delay
        }
        else{
            setDirection(180);
            if (getFiringDelay()>0){
                decFiringDelay();
            }
            else if(getWorld()->inRange(getX())) {
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                getWorld()->addActor(new PirahnaFireball(180,getX(),getY(), getWorld()));
                
                setFiringDelay();
            }
        }
    }
    
}
bool MovingObject::isSolid(){
    return false;
}
bool MovingObject::isKillsPeach(){
    return killsPeach;
}
void MovingObject::setKillsPeach(bool var){
    killsPeach = var;
}
bool MovingObject::isShell(){
    return false;
}
/**
 Moves one way and dies when it hits a barrier, codes for both fireballs and the shell class
 */
void MovingObject::doSomething(){
    if (isDead()){
        
        return;
    }
    if(!isKillsPeach()&&getWorld()->hitEnemyActor(this)&&!isDead()){
        // cout << "kileld" << endl;
        
        
        setDead();
        return;
    }
    else if (!isShell()&&isKillsPeach()&&getWorld()->overlap(this)&&!isDead()){
        //cout << "killed peach" << endl;
        getWorld()->peachTakeDmg();
        setDead();
        return;
    }
    else if (isShell()&&isKillsPeach()&&getWorld()->overlapDamageable(this)&&!isDead()){
        getWorld()->increaseScore(100);
        setDead();
        return;
    }
    
    
    //    if (!isShell()&&getWorld()->canMove(getX(), getY()-2, true)){
    //        moveTo(getX(), getY()-2);
    //
    //    }
    if (getWorld()->canMove(getX(), getY()-2, true)){
        moveTo(getX(), getY()-2);
        
    }
    if (getDirection()==0&&getWorld()->canMove(getX()+2,getY(),true)){
        moveTo(getX()+2,getY());
    }
    else if (getDirection()==180&&getWorld()->canMove(getX()-2,getY(),true)){
        moveTo(getX()-2,getY());
    }
    else{
        setDead();
    }
}
PeachFireball::PeachFireball(int direction, int x, int y, StudentWorld* world) :
MovingObject(IID_PEACH_FIRE, x, y, direction, 1, 1, false, false, world){
    setKillsPeach(false);
}
PirahnaFireball::PirahnaFireball(int direction, int x, int y, StudentWorld* world) :
MovingObject(IID_PIRANHA_FIRE, x, y, direction, 1, 1, false, false, world){
    setKillsPeach(true);
}
Shell::Shell(int direction, int x, int y, StudentWorld* world) :
MovingObject(IID_SHELL  , x, y, direction, 1, 1, false, false, world){
    setKillsPeach(true);
}
bool Shell::isShell(){
    return true;
}
