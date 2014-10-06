
#include "ScoreMenuPopup.h"
#include "MainMenu.h"
//#include "FacebookProvider.h"
//#include "Overview.h"
#include "ResourcesManager.h"
#include "FBScoreTable.h"

//#include "score/ScoreDataSource.h"
//#include "score/lb/ScoreLBDataSource.h"
//#include "score/fb/ScoreFBDataSource.h"
//#include "score/ScoreTableRenderer.h"

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

void ScoreMenuPopup::initSlidingLayer() {
    
}

void changeMenu(MenuItemSprite* item, const std::string& name) {
    Sprite* img = (Sprite*)item->getNormalImage();
    img->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
    Sprite* imgSel = (Sprite*)item->getSelectedImage();
    imgSel->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

void ScoreMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    isFriendsTab = false;
    
    float bottomOffset = ResourcesManager::getInstance()->getBottomOffset();
    
    Sprite* tabImg = Sprite::createWithSpriteFrameName("btn_score_global_sel.png");
    //tabImg->setScale(0.9);
    
    initMenuItem(menuItems, BTN_SCORE_GLOBAL, CC_CALLBACK_1(ScoreMenuPopup::menuGlobalCallback, this), Vec2(visibleSize.width/2 + origin.x - tabImg->getContentSize().width/2 - 10, visibleSize.height/2 + origin.y + 350));
    
    initMenuItem(menuItems, BTN_SCORE_FRIENDS, CC_CALLBACK_1(ScoreMenuPopup::menuFbCallback, this), Vec2(visibleSize.width/2 + origin.x + tabImg->getContentSize().width/2 + 10, visibleSize.height/2 + origin.y + 350));

    reinitTabs(menuItems, tabs);
    
    initMenuItem(menuItems, BTN_ALL_BACK, CC_CALLBACK_1(ScoreMenuPopup::menuBackCallback, this), Vec2(origin.x + visibleSize.width/2, visibleSize.height + origin.y - 800 - bottomOffset/2));
    
    std::string activeFrameName = BTN_SCORE_GLOBAL;
    changeMenu(tabs.at(0), BTN_NAME_SELECTED(activeFrameName));
    
    Sprite* bg = Sprite::createWithSpriteFrameName("bg_score_table.png");
    
  //  layer = SlidingMenuLayer::create(bg->getContentSize(), true);
  //  layer->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
  //  this->addChild(layer, 1);
    
    
/*    table = new FBScoreTable();
    //ScoreLBDataSource* dataSource = ScoreLBDataSource::create(); //ScoreDataSource::create(FacebookProvider::create())
    // ScoreFBDataSource* dataSource = ScoreFBDataSource::create();
    //ScoreDataSource* dataSource = ScoreDataSource::create();
    table->init(cocos2d::Size(bg->getContentSize().width - 150, bg->getContentSize().height - 300));
    table->setPosition(Vec2(100 + visibleSize.width/2 + origin.x - table->getContentSize().width/2, visibleSize.height/2 + origin.y - 200));
    this->addChild(table, 1002);
 */
    fbTable = new FBScoreTable();
    fbTable->init(cocos2d::Size(bg->getContentSize().width - 150, bg->getContentSize().height - 300), isFriendsTab);
    fbTable->setPosition(Vec2(100 + visibleSize.width/2 + origin.x - fbTable->getContentSize().width/2, visibleSize.height/2 + origin.y - 250));
    this->addChild(fbTable, 1002);
    
    gcTable = new GCScoreTable();
    gcTable->init(cocos2d::Size(bg->getContentSize().width - 150, bg->getContentSize().height - 300), !isFriendsTab);
    gcTable->setPosition(Vec2(100 + visibleSize.width/2 + origin.x - gcTable->getContentSize().width/2, visibleSize.height/2 + origin.y - 250));
    this->addChild(gcTable, 1002);

    if (!isFriendsTab) {
        fbTable->setVisible(false);
    }
    
 //   initSlidingLayer();
    
}

void ScoreMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}



bool doChangeTab(cocos2d::Vector<cocos2d::MenuItemSprite *> &tabs, bool isFirstTabClicked, bool isFirstTabActive) {
    if (isFirstTabActive && isFirstTabClicked == isFirstTabActive) {
        return false;
    }
    
    std::string scoreGlobal = BTN_SCORE_GLOBAL;
    std::string scoreFriend = BTN_SCORE_FRIENDS;
    std::string activeTabName = isFirstTabClicked ? BTN_NAME_SELECTED(scoreGlobal) : BTN_NAME_SELECTED(scoreFriend);
    std::string passiveTabName = isFirstTabClicked ? BTN_NAME(scoreFriend) : BTN_NAME(scoreGlobal);
    int tabIndexToActivate = isFirstTabClicked ? 0 : 1;
    int tabIndexToPassivate = isFirstTabClicked ? 1 : 0;
    
    MenuItemSprite* toActivate = tabs.at(tabIndexToActivate);
    MenuItemSprite* toPassivate = tabs.at(tabIndexToPassivate);
    
    changeMenu(toActivate, activeTabName);
    changeMenu(toPassivate, passiveTabName);
    
    return true;
}

void resetTab(bool isFirstTabActive, cocos2d::Vector<cocos2d::MenuItemSprite *> &tabs) {
    
    MenuItemSprite* toActivate = nullptr;
    MenuItemSprite* toPassivate = nullptr;
    std::string activeFrame;
    std::string passiveFrame;
    
    
    if (isFirstTabActive) {
        toActivate = tabs.at(0);
        toPassivate = tabs.at(1);
        
        activeFrame = BTN_SCORE_GLOBAL;
        passiveFrame = BTN_SCORE_FRIENDS;
    } else {
        toActivate = tabs.at(1);
        toPassivate = tabs.at(0);
        
        activeFrame = BTN_SCORE_FRIENDS;
        passiveFrame = BTN_SCORE_GLOBAL;
    }
    
    changeMenu(toActivate, BTN_NAME_SELECTED(activeFrame));
    changeMenu(toPassivate, BTN_NAME(passiveFrame));
}

void ScoreMenuPopup::menuFbCallback(cocos2d::Ref* pSender) {

    if (!isFriendsTab) {
        isFriendsTab = true;
        gcTable->setVisible(false);
        fbTable->setVisible(true);
        resetTab(false, tabs);
    
        fbTable->reload();
    }
    
    
    
    //if (doChangeTab(tabs, false, isFriendsTab)) isFriendsTab = true;
    
    //FacebookProvider::create()->share("blablastr");
}

void ScoreMenuPopup::menuGlobalCallback(cocos2d::Ref* pSender) {

    if (isFriendsTab) {
        isFriendsTab = false;
        gcTable->setVisible(true);
        fbTable->setVisible(false);
        resetTab(true, tabs);
        gcTable->reload();
    
    }
    
    
    
    //if (doChangeTab(tabs, true, isFriendsTab)) isFriendsTab = false;
    //FacebookProvider::create()->readGloabalScore();
}