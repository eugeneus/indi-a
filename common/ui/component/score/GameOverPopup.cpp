
#include "GameOverPopup.h"
#include "GameSelectMenu.h"
#include "GameMenu.h"

USING_NS_CC;

GameOverPopup::GameOverPopup(){}
GameOverPopup::~GameOverPopup() {}


GameOverPopup* GameOverPopup::create()
{
    
    GameOverPopup *pRet = new GameOverPopup();
    
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


bool GameOverPopup::init() {
    
    if (!super::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 32;
    ttfConfig.fontFilePath = "RioGrande.ttf";
    Label* label = Label::createWithTTF(ttfConfig, "Game over!");
    label->setColor(Color3B(255, 255, 255));
    label->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 100));
    this->addChild(label);
    
    return true;
}

void GameOverPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    super::initItem(menuItems, "menu_btn.png", CC_CALLBACK_1(GameOverPopup::levelSelectMenu, this));
    super::initItem(menuItems, "again_btn.png", CC_CALLBACK_1(GameOverPopup::playAgainMenu, this));
}

void GameOverPopup::levelSelectMenu(Ref* pSender) {
    this->changeScene(GameSelectMenu::createScene());
}

void GameOverPopup::playAgainMenu(Ref* pSender) {
    this->changeScene(GameMenu::createScene());
}