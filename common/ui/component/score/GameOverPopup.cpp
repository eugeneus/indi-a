
#include "GameOverPopup.h"
#include "MainMenu.h"
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
    
    Node* score = this->createScoreLabel();
    score->setPosition(Vec2(posX/2, posY/2 - 60));
    bg->addChild(score);
    
    this->addLabel(bg, ttf32, "x1", colorYellow, 1 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x2", colorYellow, 2 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x3", colorYellow, 3 * posX/4 - 60, 40);
    this->addLabel(bg, ttf32, "x4", colorYellow, 4 * posX/4 - 60, 40);
    
    return true;
}

void GameOverPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    super::initItem(menuItems, "btn_game_over_store.png", CC_CALLBACK_1(GameOverPopup::menuStoreMenu, this));
    super::initItem(menuItems, "btn_game_over_play.png", CC_CALLBACK_1(GameOverPopup::playAgainMenu, this));
    super::initItem(menuItems, "btn_game_over_quit.png", CC_CALLBACK_1(GameOverPopup::menuMainMenu, this));
}

void GameOverPopup::menuStoreMenu(Ref* pSender) {
    this->changeScene(MainMenu::createScene());
}

void GameOverPopup::menuMainMenu(Ref* pSender) {
    this->changeScene(MainMenu::createScene());
}
void GameOverPopup::playAgainMenu(Ref* pSender) {
    this->changeScene(GameMenu::createScene());
}

Node* GameOverPopup::createScoreLabel() {
    Sprite *bg = Sprite::createWithSpriteFrameName("game_over_high.png");
    //bg->setAnchorPoint(Vec2(0,0));
    //bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    return bg;
}