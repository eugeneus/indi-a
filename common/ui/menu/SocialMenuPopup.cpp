
#include "SocialMenuPopup.h"
#include "MainMenu.h"
#include "FacebookProvider.h"
#include "ResourcesManager.h"

USING_NS_CC;

SocialMenuPopup* SocialMenuPopup::create()
{
    SocialMenuPopup *pRet = new SocialMenuPopup();
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

void SocialMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    
    float bottomOffset = ResourcesManager::getInstance()->getBottomOffset();
    
    initMenuItem(menuItems, BTN_SOCIAL_FB, CC_CALLBACK_1(SocialMenuPopup::menuFbCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 250 - bottomOffset/2));
    
    initMenuItem(menuItems, BTN_SOCIAL_GP, CC_CALLBACK_1(SocialMenuPopup::menuGpCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 400 - bottomOffset/2));
    
    
    initMenuItem(menuItems, BTN_SOCIAL_INV, CC_CALLBACK_1(SocialMenuPopup::menuInviteCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 550 - bottomOffset/2));
    
    initMenuItem(menuItems, BTN_ALL_BACK, CC_CALLBACK_1(SocialMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 800 - bottomOffset/2));
}

void SocialMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}

void SocialMenuPopup::menuFbCallback(cocos2d::Ref* pSender) {
    //FacebookProvider::create()->share("blablastr");
}

void SocialMenuPopup::menuGpCallback(cocos2d::Ref* pSender) {
    //FacebookProvider::create()->readGloabalScore();
}

void SocialMenuPopup::menuInviteCallback(cocos2d::Ref* pSender) {
    
}