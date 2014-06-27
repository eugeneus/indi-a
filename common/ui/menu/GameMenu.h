
#ifndef __BlindChef__GameMenu__
#define __BlindChef__GameMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"

class GameMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
    
    cocos2d::ParallaxNode* conveyorNode;
    cocos2d::Sprite* conveyor1;
    cocos2d::Sprite* conveyor2;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
public:
    static GameMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();

    void update(float dt);
};


#endif /* defined(__BlindChef__GameMenu__) */
