
#ifndef __BlindChef__BaseGamePopup__
#define __BlindChef__BaseGamePopup__


#include "cocos2d.h"

class BaseGamePopup : public cocos2d::Layer
{
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
    void initItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& spriteFrameName, const cocos2d::ccMenuCallback& callback);
    void changeScene(cocos2d::Scene* newScene);
public:
   // BaseGamePopup();
   // virtual ~BaseGamePopup();
    virtual bool init();
};

#endif /* defined(__BlindChef__BaseGamePopup__) */
