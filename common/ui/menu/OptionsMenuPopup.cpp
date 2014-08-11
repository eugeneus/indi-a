
#include "OptionsMenuPopup.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

OptionsMenuPopup* OptionsMenuPopup::create()
{
    OptionsMenuPopup *pRet = new OptionsMenuPopup();
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

void OptionsMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    initMenuItem(menuItems, "btn_opt_music.png", CC_CALLBACK_1(OptionsMenuPopup::menuMusicCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 250));
    initMenuItem(menuItems, "btn_opt_sound.png", CC_CALLBACK_1(OptionsMenuPopup::menuSoundCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 400));
    initMenuItem(menuItems, "btn_opt_notif.png", CC_CALLBACK_1(OptionsMenuPopup::menuNotificationsCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 550));
    initMenuItem(menuItems, "btn_back.png", CC_CALLBACK_1(OptionsMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 890));
}

void OptionsMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}

void OptionsMenuPopup::menuMusicCallback(cocos2d::Ref* pSender) {
    float volume =  CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    if (volume > 0)
        volume = 0;
    else
        volume = 1;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void OptionsMenuPopup::menuSoundCallback(cocos2d::Ref* pSender) {
    float volume =  CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    if (volume > 0)
        volume = 0;
        else
            volume = 1;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void OptionsMenuPopup::menuNotificationsCallback(cocos2d::Ref* pSender) {
    
}
