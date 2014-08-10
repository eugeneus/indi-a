
#ifndef __BlindChef__GameCompletePopup__
#define __BlindChef__GameCompletePopup__

#include "cocos2d.h"
#include "BaseGamePopup.h"

class GameCompletePopup : public BaseGamePopup
{
private:
    typedef BaseGamePopup super;
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
public:
    GameCompletePopup();
    virtual ~GameCompletePopup();
    
    virtual bool init();
    
    static GameCompletePopup* create();
    
    void levelSelectMenu(cocos2d::Ref* pSender);
    void playNextMenu(cocos2d::Ref* pSender);
    void playAgainMenu(cocos2d::Ref* pSender);
};

#endif /* defined(__BlindChef__GameCompletePopup__) */
