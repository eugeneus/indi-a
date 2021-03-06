
#ifndef __BlindChef__BaseMenuPopup__
#define __BlindChef__BaseMenuPopup__

#include "cocos2d.h"
#include "ButtonConstants.h"

class BaseMenuPopup : public cocos2d::Layer
{
protected:
    cocos2d::Menu *mainMenu;
    void initMenuItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& name, const cocos2d::ccMenuCallback& callback, cocos2d::Vec2 pos);
    bool isFrameNameExist(const std::string& name);
public:
    virtual bool init();
    
    void changeScene(cocos2d::Scene* newScene);
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize);
    
    //CREATE_FUNC(MainMenuPopup);
};

#endif /* defined(__BlindChef__BaseMenuPopup__) */
