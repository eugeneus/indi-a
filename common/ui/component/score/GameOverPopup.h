
#ifndef __BlindChef__GameOverPopup__
#define __BlindChef__GameOverPopup__

#include "cocos2d.h"
#include "BaseGamePopup.h"

class GameOverPopup : public BaseGamePopup
{
private:
    typedef BaseGamePopup super;
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
public:
    GameOverPopup();
    virtual ~GameOverPopup();
    
    virtual bool init();
    
    static GameOverPopup* create();
    
    void levelSelectMenu(cocos2d::Ref* pSender);
    void playAgainMenu(cocos2d::Ref* pSender);
};

#endif /* defined(__BlindChef__GameOverPopup__) */
