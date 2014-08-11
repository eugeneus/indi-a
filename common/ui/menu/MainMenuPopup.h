#ifndef __undefensys__MainMenuPopup__
#define __undefensys__MainMenuPopup__

#include "cocos2d.h"
#include "BaseMenuPopup.h"

class MainMenuPopup : public BaseMenuPopup
{
public:
    static MainMenuPopup* create();
    
    void menuStoreCallback(cocos2d::Ref* pSender);
    void menuOptionsCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuGameCallback(cocos2d::Ref* pSender);
    
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize);
    
    //CREATE_FUNC(MainMenuPopup);
};


#endif /* defined(__undefensys__MainMenuPopup__) */
