
#include "OptionsMenu.h"
#include "OptionsMenuPopup.h"

USING_NS_CC;

OptionsMenu* OptionsMenu::create()
{
    OptionsMenu *pRet = new OptionsMenu();
    if (pRet && pRet->init("bg_opt.png"))
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

Scene* OptionsMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = OptionsMenu::create();
    scene->addChild(layer);
    return scene;
}

void OptionsMenu::initializeMenu() {
    super::initializeMenu();
    CCLOG("Options");
}


cocos2d::Layer* OptionsMenu::createMenuLayer() {
    return OptionsMenuPopup::create();
}