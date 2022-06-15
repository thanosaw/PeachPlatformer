#include "StudentWorld.h"
#include "GameConstants.h"

#include <string>
using namespace std;

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
int StudentWorld::init()
{
    Level lev(assetPath());
    
    string levelname = "level01.txt";
    Level::LoadResult result = lev.loadLevel(levelname);
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
                     cout << "Location 5,10 is empty" << endl;
                     break;
                     
                     case Level::peach:
                        m_peach = new Peach(i*8,j*8,this);
                     cout << "Location 5,10 is where Peach starts" << endl;
                     break;
                     
                    case Level::koopa:
                        
                        break;
                    case Level::goomba:
                        
                        break;
                    case Level::piranha:
                        
                        break;
                    case Level::block:
                        addActor(new Block(i*8,j*8,this));
                        cout << "Location 5,10 holds a regular block" << endl;
                        break;
                        
                    case Level::star_goodie_block:
                        
                        break;
                    case Level::mushroom_goodie_block:
                        
                        break;
                    case Level::flower_goodie_block:
                        
                        break;
                    case Level::pipe:
                        
                        break;
                    case Level::flag:
                        
                        break;
                    case Level::mario:
                        
                        break;
                }
            }
        }
        
        
        
    }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    //for (int i=0;i<m_nActors;i++){
        Actor* actor;
        actor = m_peach;
    actor->doSomething();
    for (Actor* act: m_actors){
        act->doSomething();
    }
//        if (!actor.isDead()){
//            actor->doSomething();
//            if (m_peach.isDead()){
//                decLives();
//                //TODO: Play sound of death
//                return GWSTATUS_PLAYER_DIED;
//            }
//
//        }

  //  }
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    m_peach = nullptr;
    for (Actor* a: m_actors){
        delete a;
    }
    m_actors.clear();
    
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
bool StudentWorld::canMove(int x, int y){
    for(Actor* act:m_actors){
        if (act->getX()<x+SPRITE_WIDTH-1&&x<act->getX()+SPRITE_WIDTH-1&&act->getY()<y+SPRITE_WIDTH-1&&y<act->getY()+SPRITE_WIDTH-1){
            return false;
        }
    }
    return true;
}
