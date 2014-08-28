
#include "SocialMenuPopup.h"
#include "MainMenu.h"
#include "FacebookProvider.h"

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
    initMenuItem(menuItems, "btn_soc_fb.png", CC_CALLBACK_1(SocialMenuPopup::menuFbCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 250));
    
    initMenuItem(menuItems, "btn_soc_gp.png", CC_CALLBACK_1(SocialMenuPopup::menuGpCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 400));
    
    
    initMenuItem(menuItems, "btn_soc_inv.png", CC_CALLBACK_1(SocialMenuPopup::menuInviteCallback, this), Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 550));
    
    initMenuItem(menuItems, "btn_back.png", CC_CALLBACK_1(SocialMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 800));
}

void SocialMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}

void SocialMenuPopup::menuFbCallback(cocos2d::Ref* pSender) {
    FacebookProvider::create()->share("blablastr");
}

void SocialMenuPopup::menuGpCallback(cocos2d::Ref* pSender) {
   
}

void SocialMenuPopup::menuInviteCallback(cocos2d::Ref* pSender) {
    
}