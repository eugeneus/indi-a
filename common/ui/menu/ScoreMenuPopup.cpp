
#include "ScoreMenuPopup.h"
#include "MainMenu.h"
#include "FacebookProvider.h"

USING_NS_CC;

ScoreMenuPopup* ScoreMenuPopup::create()
{
    ScoreMenuPopup *pRet = new ScoreMenuPopup();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void reinitTabs(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vector<cocos2d::MenuItemSprite *> &tabs) {
    for (MenuItem* tab : menuItems) {
        tab->setScale(0.9);
        tabs.pushBack((MenuItemSprite*)tab);
    }
}

void ScoreMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    isFriendsTab = false;
    
    Sprite* tabImg = Sprite::createWithSpriteFrameName("btn_score_global_sel.png");
    //tabImg->setScale(0.9);
    
    initMenuItem(menuItems, "btn_score_global_sel.png", CC_CALLBACK_1(ScoreMenuPopup::menuGlobalCallback, this), Vec2(visibleSize.width/2 + origin.x - tabImg->getContentSize().width/2*0.9, visibleSize.height/2 + origin.y + 390));
    
    initMenuItem(menuItems, "btn_score_friends.png", CC_CALLBACK_1(ScoreMenuPopup::menuFbCallback, this), Vec2(visibleSize.width/2 + origin.x + tabImg->getContentSize().width/2*0.9, visibleSize.height/2 + origin.y + 390));

    reinitTabs(menuItems, tabs);
    
    initMenuItem(menuItems, "btn_back.png", CC_CALLBACK_1(ScoreMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 800));
}

void ScoreMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}

void changeMenu(MenuItemSprite* item, const std::string& name) {
    Sprite* img = (Sprite*)item->getNormalImage();
    img->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    Sprite* imgSel = (Sprite*)item->getSelectedImage();
    imgSel->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

bool doChangeTab(cocos2d::Vector<cocos2d::MenuItemSprite *> &tabs, bool isFirstTabClicked, bool isFirstTabActive) {
    if (isFirstTabActive && isFirstTabClicked == isFirstTabActive) {
        return false;
    }
    
    std::string activeTabName = isFirstTabClicked ? "btn_score_global_sel.png" : "btn_score_friends_sel.png";
    std::string passiveTabName = isFirstTabClicked ? "btn_score_friends.png" : "btn_score_global.png";
    int tabIndexToActivate = isFirstTabClicked ? 0 : 1;
    int tabIndexToPassivate = isFirstTabClicked ? 1 : 0;
    
    MenuItemSprite* toActivate = tabs.at(tabIndexToActivate);
    MenuItemSprite* toPassivate = tabs.at(tabIndexToPassivate);
    
    changeMenu(toActivate, activeTabName);
    changeMenu(toPassivate, passiveTabName);
    
    return true;
}

void ScoreMenuPopup::menuFbCallback(cocos2d::Ref* pSender) {

    if (doChangeTab(tabs, false, isFriendsTab)) isFriendsTab = true;
    
    //FacebookProvider::create()->share("blablastr");
}

void ScoreMenuPopup::menuGlobalCallback(cocos2d::Ref* pSender) {

    
    if (doChangeTab(tabs, true, isFriendsTab)) isFriendsTab = false;
    //FacebookProvider::create()->readGloabalScore();
}