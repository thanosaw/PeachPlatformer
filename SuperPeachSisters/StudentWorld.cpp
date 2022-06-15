#include "StudentWorld.h"
#include "GameConstants.h"
#include <sstream>
#include <string>
using namespace std;
void StudentWorld::finishLevel(){
    m_levelComplete=true;
    
}
GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath) , m_nActors(0)
{
    m_actors.clear();
    m_peach = nullptr;
    
}
void StudentWorld::addActor(   Actor* actor ){
    m_actors.push_back(actor);
    m_nActors++;
    return;
}
void StudentWorld::addFlower(int x, int y){
    m_actors.push_back(new Flower(x, y, this));
}
void StudentWorld::addMushroom(int x, int y){
    m_actors.push_back(new Mushroom(x, y, this));
}
void StudentWorld::addStar(int x, int y){
    m_actors.push_back(new Star(x, y, this));
}
/**
 Initializes the entire level
 */
int StudentWorld::init()
{
    
    m_levelComplete=false;
    Level lev(assetPath());
    string levelname;
    //    switch (getLevel()){
    //        case 1:
    //            levelname = "level01.txt";
    //            break;
    //        case 2:
    //            levelname = "level02.txt";
    //            break;
    //        case 3:
    //            levelname = "level03.txt";
    //            break;
    //
    //    }
    
    if (getLevel()<10){
        levelname =  "0"+ to_string(getLevel());
    }
    else{
        levelname = to_string(getLevel());
    }
    
    string res = "level" + levelname + ".txt";
//    res = "level03.txt";
    Level::LoadResult result = lev.loadLevel(res);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "level01.txt is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for (int i=0;i<32;i++){
            for (int j=0;j<32;j++){
                
                ge = lev.getContentsOf(i, j); // x=5, y=10
                switch (ge){
                    case Level::empty:
                        
                        break;
                        
                    case Level::peach:
                        
                        m_peach = new Peach(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this);
                        
                        break;
                        
                    case Level::koopa:
                        addActor(new Koopa(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        break;
                    case Level::goomba:
                        addActor(new Goomba(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        break;
                    case Level::piranha:
                        addActor(new Pirahna(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        break;
                    case Level::block:
                        addActor(new Block(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        
                        break;
                        
                    case Level::star_goodie_block:
                        addActor(new StarBlock(true, i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        break;
                    case Level::mushroom_goodie_block:
                        addActor(new MushroomBlock(true, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::flower_goodie_block:
                        addActor(new FlowerBlock(true, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                    case Level::pipe:
                        addActor(new Pipe(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        
                        break;
                    case Level::flag:
                        addActor(new Flag(false, i*SPRITE_WIDTH,j*SPRITE_HEIGHT,this));
                        break;
                    case Level::mario:
                        addActor(new Mario(false,  i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this));
                        break;
                }
            }
        }
        
        
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}
/**
 Executes certain actions during each tick
 */
int StudentWorld::move()
{
    if (m_gameWon){
        return GWSTATUS_PLAYER_WON;
    }


    
    vector<Actor*>::iterator itr;
    itr = m_actors.begin();
    while (itr!=m_actors.end()){
        if (!(*itr)->isDead()){
            (*itr)->doSomething();
            if (m_peach->isDead()){
                decLives();
                //playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            if (m_levelComplete){
                
                return GWSTATUS_FINISHED_LEVEL;
            }
            
        }
        itr++;
    }
    m_peach->doSomething();
    
    for (auto itr = m_actors.begin(); itr != m_actors.end(); itr++) {
        if ((*itr)->isDead()) {
            delete *itr;
            m_actors.erase(itr);
            itr = m_actors.begin();
        }
    }
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(0);
    oss << "Lives: " << getLives() << "  ";
    oss << "Level: " << setw(2) << setfill('0') <<getLevel() << "  ";
    oss <<  "Score: " << setw(6) << setfill('0') << getScore() << " ";
    
    if (m_peach->hasStar()){
        oss << "StarPower!" << " ";
    }
    if (m_peach->hasFlower()){
        oss << "ShootPower!" << " ";
    }
    if (m_peach->hasMushroom()){
        oss << "JumpPower!" << " ";
    }
    setGameStatText(oss.str());
    
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    return GWSTATUS_CONTINUE_GAME;
}
/**
 Clears everything from the screen, also can be used as destructor and frees dynamically allocated memory
 */
void StudentWorld::cleanUp()
{
    delete m_peach;
    m_peach = nullptr;
    for (Actor* a: m_actors){
        delete a;
    }
    m_actors.clear();
    
}
/**
 Destructor
 */
StudentWorld::~StudentWorld(){
    cleanUp();
}
/**
 Checks if an area of a grid contains another SPRITE, if not returns false, if yes returns true
 */
bool StudentWorld::canMove(int x, int y, bool ground){ //Ground = cant bonk, if ground is true then it cannot bonk
    bool ret = true;
//    for(Actor* act:m_actors){
//
//        if (act->getX()< x+SPRITE_WIDTH-1 && x < act->getX() + SPRITE_WIDTH -1&& act->getY()<y+SPRITE_HEIGHT-1 && y < act->getY()+SPRITE_HEIGHT-1&&act->isSolid()){
//
//            if (!ground){
//                //                cout << "y:" << y << endl;
//                //                cout << "here" << endl;
//                act->bonk();
//            }
//
//            ret = false;
//        }
//        if (act->getX()< x+SPRITE_WIDTH-1 && x < act->getX() + SPRITE_WIDTH -1&& act->getY()<y+SPRITE_HEIGHT-1 && y < act->getY()+SPRITE_HEIGHT-1&&!act->isSolid()){
//
//            if (!ground){
//                //                cout << "y:" << y << endl;
//                //                cout << "here" << endl;
//                act->bonk();
//            }
//
//
//        }
//
//    }
     for(Actor* act:m_actors){
 
         if (act->getX()< x+SPRITE_WIDTH && x < act->getX() + SPRITE_WIDTH && act->getY()<y+SPRITE_HEIGHT && y < act->getY()+SPRITE_HEIGHT&&act->isSolid()){
 
             if (!ground){
                 //                cout << "y:" << y << endl;
                 //                cout << "here" << endl;
                 act->bonk();
             }
 
             ret = false;
             
         }
         if (act->getX()< x+SPRITE_WIDTH && x < act->getX() + SPRITE_WIDTH && act->getY()<y+SPRITE_HEIGHT && y < act->getY()+SPRITE_HEIGHT&&!act->isSolid()){
 
             if (!ground){
                 //                cout << "y:" << y << endl;
                 //                cout << "here" << endl;
                 act->bonk();
             }
 
 
         }
 
     }
    //overlap(m_peach->getX(), act->getX(), m_peach->getY(), act->getY())
    
    return ret;
}
/**
 Checks if an actor overlaps with Peach
 */
bool StudentWorld::overlap(Actor* a){ 
    int x1 = a->getX();
    int y1 = a->getY();
    int x2 = m_peach->getX();
    int y2 = m_peach->getY();
    if (x1 < x2+SPRITE_WIDTH&& x2 < x1 + SPRITE_WIDTH&&y1 < y2 + SPRITE_HEIGHT && y2<y1 + SPRITE_HEIGHT){
        return true;
    }
    return false;
}
/**
 Checks if two actors a and b overlap.
 */
bool StudentWorld::overlap(Actor* a,Actor* b){
    int x1 = a->getX();
    int y1 = a->getY();
    int x2 = b->getX();
    int y2 = b->getY();
    if (x1 < x2+SPRITE_WIDTH&& x2 < x1 + SPRITE_WIDTH&&y1 < y2 + SPRITE_HEIGHT && y2<y1 + SPRITE_HEIGHT){
        return true;
    }
    return false;
}
/**
 BELOW THREE FUNCTIONS:
 Gives Peach the Powerups
 */
void StudentWorld::flowerPower(){
    m_peach->canShoot();
    m_peach->hpUp();
//    cout << m_peach->getHp() << endl;
}
void StudentWorld::mushroomPower(){
    m_peach->gotMushroom();
    m_peach->hpUp();
}
void StudentWorld::starPower(){
    m_peach->gotStar();
    
}
/**
 Makes actor takeDamage
 */
void StudentWorld::takeDamage(Actor* act){
    act->setDead();
}
/**
 Behavior for Peach if she happens to take damage, either sets her to dead or gets rid of her powerup and gives her temporary invincibility.
 */
void StudentWorld::peachTakeDmg(){
    //    cout << "take one damg" << endl;
    if (m_peach->isInvincible())
        return;
    m_peach->setInvTickCount(10);
    m_peach->losePower();
    m_peach->decHp();
    if (m_peach->getHp()!=1){
        playSound(SOUND_PLAYER_HURT);
    }
}
/**
 Checks if peach currently has a starpower
 */
bool StudentWorld::hasStar(){
    return m_peach->hasStar();
}
/**
 Checks if a certain actor has collided with a damageable actor
 */
bool StudentWorld::hitEnemyActor(Actor* hitActor ){
    vector<Actor*>::iterator itr;
    itr = m_actors.begin();
    while (itr!=m_actors.end()){
        //        int a= (*itr)->getX(), b=(*itr)->getY(), dir = (*itr)->getDirection();
        if (overlap(*itr, hitActor)&&(*itr)->isDamageable()){
            
            (*itr)->setDead();
            
            //            addShell(a,b,dir);
            increaseScore((*itr)->getScoreIncrease());
            return true;
        }
        itr++;
    }
    return false;
}
/**
 Returns if Peach is in range of a certain y value (Pirahna's y val)
 */
bool StudentWorld::pirahnaTargeting( int y)
{
    if (m_peach->getY()<y+1.5*SPRITE_HEIGHT&&m_peach->getY()>y-1.5*SPRITE_HEIGHT){
        return true;
    }
    return false;
}
/**
 Finds which side of a certain x value Peach is on
 */
bool StudentWorld::onRight(int x)
{
    if (m_peach->getX()>x){
        return true;
    }
    return false;
}
/**
 Checks if Peach is in range of a certain x value
 */
bool StudentWorld::inRange(int x){
    if (m_peach->getX()-x<SPRITE_WIDTH*8&&x-m_peach->getX()<SPRITE_WIDTH*8){
        return true;
    }
    return false;
}
/**
 Adds a shell to the grid with a specified x, y ,direction
 */
void StudentWorld::addShell(int x, int y, int direction){
    m_actors.push_back(new Shell(direction, x, y, this));
}
/**
 Checks if a certain actor has overalapped with a damageable actor (used for shell, and fireballs)
 */
bool StudentWorld::overlapDamageable(Actor* me){
    for (auto a: m_actors){
        if (a!=me&&!a->isDead()&&a->isDamageable()&&overlap(me, a)){
            a->setDead();
            return true;
        }
    }
    return false;
}
/**
 Sets the game to won, game over
 */
void StudentWorld::gameWon(){
    m_gameWon=true;
}
