
#ifndef __BlindChef__SocialMenu__
#define __BlindChef__SocialMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"

class SocialMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
public:
    static SocialMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();
    
    virtual cocos2d::Layer* createMenuLayer();
};

#endif /* defined(__BlindChef__SocialMenu__) */
