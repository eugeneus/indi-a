
#ifndef __BlindChef__GameMenu__
#define __BlindChef__GameMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"
#include "Conveyor.h"
#include "Hands.h"

class MovementController;
class GameController;

class GameMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
   
    GameController* _theGameController;

   
    cocos2d::ParallaxNode* conveyorNode;
    cocos2d::Sprite* conveyor1;
    cocos2d::Sprite* conveyor2;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    Conveyor* conv;
    Hands* hands;
    
    float lastCreatedItem;
    int nextItemDt;
    
    float yPosCheckGrab;
    float yPosStartGrab;
   
   MovementController* _mover;
protected:
    void update(float dt);
public:
    static GameMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();
};


#endif /* defined(__BlindChef__GameMenu__) */
