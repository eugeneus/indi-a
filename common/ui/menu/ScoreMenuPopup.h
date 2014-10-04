
#ifndef __BlindChef__ScoreMenuPopup__
#define __BlindChef__ScoreMenuPopup__

#include "cocos2d.h"
#include "BaseMenuPopup.h"
#include "FBScoreTable.h"
#include "GCScoreTable.h"

class ScoreMenuPopup : public BaseMenuPopup
{
private:
    bool isFriendsTab;
    cocos2d::Vector<cocos2d::MenuItemSprite *> tabs;
    FBScoreTable* table;
    GCScoreTable *gcTable;
public:
    static ScoreMenuPopup* create();
    
    void menuBackCallback(cocos2d::Ref* pSender);
    void menuFbCallback(cocos2d::Ref* pSender);
    void menuGlobalCallback(cocos2d::Ref* pSender);
    
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize);
    void initSlidingLayer() ;
    //CREATE_FUNC(MainMenuPopup);
};

#endif /* defined(__BlindChef__ScoreMenuPopup__) */
