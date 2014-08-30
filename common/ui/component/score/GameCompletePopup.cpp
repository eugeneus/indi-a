
#include "GameCompletePopup.h"
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
    
    Sprite *bg = Sprite::createWithSpriteFrameName("bg_game_over.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    this->addChild(bg, 0);
    
    TTFConfig ttf32;
    ttf32.fontSize = 32;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    TTFConfig ttf48;
    ttf48.fontSize = 48;
    ttf48.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorYellow = Color3B(255, 240, 104);
    const cocos2d::Color3B& colorWhite = Color3B(255, 255, 255);
    
    float posX = bg->getContentSize().width;
    float posY = bg->getContentSize().height;
    
    Label* score1 = this->createLabel(ttf48, "456000", colorYellow);
    Label* score2 = this->createLabel(ttf48, "pts", colorWhite);
    this->addLabelsLine(bg, score1, score2, posX/2, posY - 200);
    
    Label* dishes1 = this->createLabel(ttf32, "38", colorYellow);
    Label* dishes2 = this->createLabel(ttf32, "dishes served", colorWhite);
    this->addLabelsLine(bg, dishes1, dishes2, posX/2, posY - 250);
    
    this->addLabel(bg, ttf32, "x1", colorYellow, 1 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x2", colorYellow, 2 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x3", colorYellow, 3 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x4", colorYellow, 4 * posX/4 - 60, 40);
    
    return true;
}

void GameCompletePopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    super::initItem(menuItems, "menu_btn.png", CC_CALLBACK_1(GameCompletePopup::levelSelectMenu, this));
    super::initItem(menuItems, "again_btn.png", CC_CALLBACK_1(GameCompletePopup::playNextMenu, this));
    super::initItem(menuItems, "again_btn.png", CC_CALLBACK_1(GameCompletePopup::playAgainMenu, this));
}

void GameCompletePopup::levelSelectMenu(Ref* pSender) {
    //this->changeScene(GameSelectMenu::createScene());
}

void GameCompletePopup::playNextMenu(Ref* pSender) {
    this->changeScene(GameMenu::createScene());
}

void GameCompletePopup::playAgainMenu(Ref* pSender) {
    super::changeScene(GameMenu::createScene());
}