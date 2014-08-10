
#include "GameCompletePopup.h"
#include "GameSelectMenu.h"
#include "GameMenu.h"

USING_NS_CC;

GameCompletePopup::GameCompletePopup(){}
GameCompletePopup::~GameCompletePopup() {}


GameCompletePopup* GameCompletePopup::create()
{
    
    GameCompletePopup *pRet = new GameCompletePopup();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool GameCompletePopup::init() {
    
    if (!super::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 32;
    ttfConfig.fontFilePath = "RioGrande.ttf";
    Label* label = Label::createWithTTF(ttfConfig, "Game complete!");
    label->setColor(Color3B(100, 200, 200));
    label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 100));
    this->addChild(label);
    
    return true;
}

void GameCompletePopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    super::initItem(menuItems, "menu_btn.png", CC_CALLBACK_1(GameCompletePopup::levelSelectMenu, this));
    super::initItem(menuItems, "again_btn.png", CC_CALLBACK_1(GameCompletePopup::playNextMenu, this));
    super::initItem(menuItems, "again_btn.png", CC_CALLBACK_1(GameCompletePopup::playAgainMenu, this));
}

void GameCompletePopup::levelSelectMenu(Ref* pSender) {
    this->changeScene(GameSelectMenu::createScene());
}

void GameCompletePopup::playNextMenu(Ref* pSender) {
    this->changeScene(GameMenu::createScene());
}

void GameCompletePopup::playAgainMenu(Ref* pSender) {
    super::changeScene(GameMenu::createScene());
}