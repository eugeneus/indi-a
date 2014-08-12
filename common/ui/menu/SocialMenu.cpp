
#include "SocialMenu.h"
#include "SocialMenuPopup.h"

USING_NS_CC;

SocialMenu* SocialMenu::create()
{
    SocialMenu *pRet = new SocialMenu();
    if (pRet && pRet->init("bg_social.png"))
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

Scene* SocialMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = SocialMenu::create();
    scene->addChild(layer);
    return scene;
}

void SocialMenu::initializeMenu() {
    super::initializeMenu();
    CCLOG("Social");
}


cocos2d::Layer* SocialMenu::createMenuLayer() {
    return SocialMenuPopup::create();
}