#include "MainMenuPopup.h"
#include "OptionsMenu.h"

#include "GameMenu.h"
#include "SocialMenu.h"
#include "ScoreMenu.h"

USING_NS_CC;

MainMenuPopup* MainMenuPopup::create()
{
    MainMenuPopup *pRet = new MainMenuPopup();
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

void MainMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    initMenuItem(menuItems, "btn_main_play.png", CC_CALLBACK_1(MainMenuPopup::menuGameCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 180));
    initMenuItem(menuItems, "btn_main_store.png", CC_CALLBACK_1(MainMenuPopup::menuStoreCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 400));
    initMenuItem(menuItems, "btn_main_score.png", CC_CALLBACK_1(MainMenuPopup::menuScoreCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 550));
    initMenuItem(menuItems, "btn_main_opt.png", CC_CALLBACK_1(MainMenuPopup::menuOptionsCallback, this), Vec2(visibleSize.width/2 + origin.x - 100, visibleSize.height + origin.y - 700));
    initMenuItem(menuItems, "btn_main_soc.png", CC_CALLBACK_1(MainMenuPopup::menuSocialCallback, this), Vec2(visibleSize.width/2 + origin.x + 100, visibleSize.height + origin.y - 700));
    initMenuItem(menuItems, "btn_main_exit.png", CC_CALLBACK_1(MainMenuPopup::menuExitCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 820));
}

void MainMenuPopup::menuOptionsCallback(Ref* pSender) {
    Scene *newScene = OptionsMenu::createScene();
    this->changeScene(newScene);
}

void MainMenuPopup::menuStoreCallback(Ref* pSender) {
    Scene *newScene = OptionsMenu::createScene();
    this->changeScene(newScene);
}

void MainMenuPopup::menuScoreCallback(Ref* pSender) {
    Scene *newScene = ScoreMenu::createScene();
    this->changeScene(newScene);
}

void MainMenuPopup::menuSocialCallback(Ref* pSender) {
    Scene *newScene = SocialMenu::createScene();
    this->changeScene(newScene);
}

void MainMenuPopup::menuGameCallback(Ref* pSender) {
    Scene *newScene = GameMenu::createScene();
    this->changeScene(newScene);
}

void MainMenuPopup::menuExitCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuPopup::menuCloseCallback(Ref* pSender) {
    this->removeFromParentAndCleanup(true);
}

