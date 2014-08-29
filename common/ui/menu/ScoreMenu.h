
#ifndef __BlindChef__ScoreMenu__
#define __BlindChef__ScoreMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"

class ScoreMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
public:
    static ScoreMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();
    
    virtual cocos2d::Layer* createMenuLayer();
};

#endif /* defined(__BlindChef__ScoreMenu__) */
