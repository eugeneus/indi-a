
#ifndef __BlindChef__GameOverPopup__
#define __BlindChef__GameOverPopup__

#include "cocos2d.h"
#include "BaseGamePopup.h"

class GameOverPopup : public BaseGamePopup
{
private:
    typedef BaseGamePopup super;
    cocos2d::Sprite *bg;
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
    void update(float dt);
    void checkLives();
public:
    GameOverPopup();
    virtual ~GameOverPopup();
    
    virtual bool init();
    
    static GameOverPopup* create();
    
    void menuMainMenu(cocos2d::Ref* pSender);
    void menuStoreMenu(cocos2d::Ref* pSender);
    void menuSocMenu(cocos2d::Ref* pSender);
    void playAgainMenu(cocos2d::Ref* pSender);
    
    cocos2d::Node* createScoreLabel();
};

#endif /* defined(__BlindChef__GameOverPopup__) */
