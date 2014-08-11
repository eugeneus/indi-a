
#ifndef __BlindChef__SocialMenuPopup__
#define __BlindChef__SocialMenuPopup__

#include "cocos2d.h"
#include "BaseMenuPopup.h"

class SocialMenuPopup : public BaseMenuPopup
{
public:
    static SocialMenuPopup* create();
    
    void menuBackCallback(cocos2d::Ref* pSender);
    void menuFbCallback(cocos2d::Ref* pSender);
    void menuGpCallback(cocos2d::Ref* pSender);
    void menuInviteCallback(cocos2d::Ref* pSender);
    
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize);
    
    //CREATE_FUNC(MainMenuPopup);
};


#endif /* defined(__BlindChef__SocialMenuPopup__) */
