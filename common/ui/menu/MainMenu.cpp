
#include "MainMenu.h"
#include "MainMenuPopup.h"
#include "SimpleAudioEngine.h"
#include "SoundsConstants.h"
#include "UserDataProvider.h"

USING_NS_CC;

MainMenu* MainMenu::create()
{
    MainMenu *pRet = new MainMenu();
    if (pRet && pRet->init("bg_main.png"))
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

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

void MainMenu::initializeMenu() {
    
    CCLOG("Main Menu");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images.plist");
    SpriteBatchNode *spriteBatch = SpriteBatchNode::create("images.png");
    this->addChild(spriteBatch);
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_CLICK);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_FALL_ITEM);
    
    bool isSoundOn = UserDataProvider::getInstance()->isSoundOn();
    bool isMusicOn = UserDataProvider::getInstance()->isMusicOn();
    
    float soundVolume = isSoundOn ? 1.0 : 0.0;
    float musicVolume = isMusicOn ? 1.0 : 0.0;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(soundVolume);
}

cocos2d::Layer* MainMenu::createMenuLayer() {
    return MainMenuPopup::create();
}