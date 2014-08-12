
#ifndef __BlindChef__OptionsMenuPopup__
#define __BlindChef__OptionsMenuPopup__

#include "cocos2d.h"
#include "BaseMenuPopup.h"

class OptionsMenuPopup : public BaseMenuPopup
{
public:
    static OptionsMenuPopup* create();
    
    void menuBackCallback(cocos2d::Ref* pSender);
    void menuMusicCallback(cocos2d::Ref* pSender);
    void menuSoundCallback(cocos2d::Ref* pSender);
    void menuNotificationsCallback(cocos2d::Ref* pSender);
    
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize);
    void initMenuItemTrigger(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& name, const cocos2d::ccMenuCallback& callback, cocos2d::Vec2 pos, int tag);
    
    void toggleMenuItemByTag(int tag, const char* format, bool isON);
    
    //CREATE_FUNC(MainMenuPopup);
};


#endif /* defined(__BlindChef__OptionsMenuPopup__) */
