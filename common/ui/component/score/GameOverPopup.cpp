
#include "GameOverPopup.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "UserDataProvider.h"
#include "SoundsConstants.h"
#include "GKHWrapperCpp.h"
#include "FBManager.h"

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

static inline long millisecondNow()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

bool GameOverPopup::init() {
    
    if (!super::init()) {
        return false;
    }
    
  //  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_TIMER_END);
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::createWithSpriteFrameName("bg_game_over.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);
    
    TTFConfig ttf32;
    ttf32.fontSize = 64;
    ttf32.fontFilePath = "BrownBagLunch.ttf";
    ttf32.outlineSize = 1;
    
    TTFConfig ttf48;
    ttf48.fontSize = 96;
    ttf48.fontFilePath = "BrownBagLunch.ttf";
    ttf48.outlineSize = 1;
    
    const cocos2d::Color3B& colorBlack = Color3B(0, 0, 0);
    const cocos2d::Color3B& colorRed = Color3B(255, 0, 0);
    
    float posX = bg->getContentSize().width;
    float posY = bg->getContentSize().height;
   
    UserDataProvider *userData = UserDataProvider::getInstance();
    
    int score = userData->getUserScore();
    int bestScore = userData->getBestUserScore();
    
    if (bestScore < score) {
        userData->updateBestUserScore(score);
        
        GKHWrapperCpp *gkProvider = new GKHWrapperCpp();
        gkProvider->submitScoreToCatagory(score, "bc_scores_top");
        
        [FBManager postBestResult:score];
    }
    
    /*Label* score1 = this->createLabel(ttf48, CCString::createWithFormat("%i", score)->getCString(), colorYellow);
    score1->setOpacity(120);
    Label* score2 = this->createLabel(ttf48, "pts", colorWhite);
    score2->setOpacity(120);
    this->addLabelsLine(bg, score1, score2, posX/2, posY - 200);*/
    
    /*int dishesCount = userData->getDishesCount();
    Label* dishes1 = this->createLabel(ttf32, CCString::createWithFormat("%i", dishesCount)->getCString(), colorYellow); //TODO:
    dishes1->setOpacity(120);
    Label* dishes2 = this->createLabel(ttf32, "dishes served", colorWhite);
    dishes2->setOpacity(120);
    this->addLabelsLine(bg, dishes1, dishes2, posX/2, posY - 250);*/
    
    Node* scoreLabel = this->createScoreLabel();
    scoreLabel->setPosition(Vec2(posX/2, posY - 180 - scoreLabel->getContentSize().height/2));
    bg->addChild(scoreLabel);
    
    Label* score2 = Label::createWithTTF(ttf48, CCString::createWithFormat("%i", score)->getCString());
    //label->setAlignment(TextHAlignment::LEFT);
    //label->setLineBreakWithoutSpace(0);
    score2->setAnchorPoint(Vec2(0,0));
    score2->setColor(colorRed);
    score2->setPosition(Vec2(posX/2, scoreLabel->getPosition().y - scoreLabel->getContentSize().height/2 - 80));
    score2->setTag(1);
    score2->setOpacity(120);
    
    bg->addChild(score2);
    
    int lives = userData->getUserLives();
    
    lives--;
    long now = millisecondNow();
    userData->updateLiveTimeout(0, CCString::createWithFormat("%li", now)->getCString());
    
    /*if (lives == 0) {
        this->scheduleUpdate();
    }*/
    userData->updateUserLives(lives);
    
    std::string spriteFrameName = BTN_GAME_OVER_EXIT;
    std::string spriteNormalFrameName = BTN_NAME(spriteFrameName);
    std::string spriteSelectedFrameName = BTN_NAME_SELECTED(spriteFrameName);
    if (!SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteSelectedFrameName)) spriteSelectedFrameName = BTN_NAME(spriteFrameName);
    
    MenuItem* item = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrameName(spriteNormalFrameName),
                                            Sprite::createWithSpriteFrameName(spriteSelectedFrameName),
                                            CC_CALLBACK_1(GameOverPopup::menuMainMenu, this));
    
    Menu *mainMenu1 = Menu::createWithItem(item);
    mainMenu1->setPosition(Vec2(100 + origin.x, origin.y + 150));
    this->addChild(mainMenu1, 1);
    
    /*int bonus1Count = userData->getBonus1Count();
    int bonus2Count = userData->getBonus2Count();
    int bonus3Count = userData->getBonus3Count();
    
    this->addLabel(bg, ttf32, CCString::createWithFormat("x%i", lives)->getCString(), colorYellow, 1 * posX/4 - 60, 40, 100);
    this->addLabel(bg, ttf32, CCString::createWithFormat("x%i", bonus1Count)->getCString(), colorYellow, 2 * posX/4 - 60, 40, 101);
    this->addLabel(bg, ttf32, CCString::createWithFormat("x%i", bonus2Count)->getCString(), colorYellow, 3 * posX/4 - 60, 40, 102);
    this->addLabel(bg, ttf32, CCString::createWithFormat("x%i", bonus3Count)->getCString(), colorYellow, 4 * posX/4 - 60, 40, 103);
    
    */
    return true;
}

void GameOverPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    super::initItem(menuItems, BTN_GAME_OVER_SOC, CC_CALLBACK_1(GameOverPopup::menuSocMenu, this));
    super::initItem(menuItems, BTN_GAME_OVER_STORE, CC_CALLBACK_1(GameOverPopup::menuStoreMenu, this));
    super::initItem(menuItems, BTN_GAME_OVER_PLAY, CC_CALLBACK_1(GameOverPopup::playAgainMenu, this));
   // super::initItem(menuItems, BTN_GAME_OVER_EXIT, CC_CALLBACK_1(GameOverPopup::menuMainMenu, this));
}

void GameOverPopup::menuStoreMenu(Ref* pSender) {
    this->changeScene(MainMenu::createScene());
}

void GameOverPopup::menuSocMenu(Ref* pSender) {
    int score = UserDataProvider::getInstance()->getUserScore();
    [FBManager postBestResult: score];
}

void GameOverPopup::menuMainMenu(Ref* pSender) {
    this->changeScene(MainMenu::createScene());
}
void GameOverPopup::playAgainMenu(Ref* pSender) {
    if (UserDataProvider::getInstance()->getUserLives() > 0) {
        this->changeScene(GameMenu::createScene());
    } else {
        //TODO: purchases;
    }
}

Node* GameOverPopup::createScoreLabel() {
    Sprite *bg = Sprite::createWithSpriteFrameName("game_over_high.png");
    //bg->setAnchorPoint(Vec2(0,0));
    //bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    return bg;
}

void GameOverPopup::update(float dt) {
    this->checkLives();
    // }
}

void GameOverPopup::checkLives() {
    int livesCount = UserDataProvider::getInstance()->getUserLives();
    if (livesCount < 10) {
        long now = millisecondNow();
        // for (int i=livesCount + 1; i < 10 + 1; i ++) {
        std::string timeout = UserDataProvider::getInstance()->getLiveTimeout(0);
        long t = atol(timeout.c_str());
        if (t != 0 && now - t > 10 * 60 * 1000) { // 10 min
            int count = (int)round ((now - t) / 10.0 * 60 * 1000);
            if (count < 0 || count == 0) count = 1;
            livesCount += count;
            if (livesCount > 10) livesCount = 10;
            
            UserDataProvider::getInstance()->updateLiveTimeout(0, CCString::createWithFormat("%li", now)->getCString());
            UserDataProvider::getInstance()->updateUserLives(livesCount);
            Label* lbl = (Label *)bg->getChildByTag(100);
            lbl->setString(CCString::createWithFormat("x%i", livesCount)->getCString());
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BONUS_PICKUP);
        }
        // }
    }
}