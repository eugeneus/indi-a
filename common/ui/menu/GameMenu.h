
#ifndef __BlindChef__GameMenu__
#define __BlindChef__GameMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"

class GameMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
public:
    static GameMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();
};


#endif /* defined(__BlindChef__GameMenu__) */
