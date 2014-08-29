
#include "ScoreMenu.h"
#include "ScoreMenuPopup.h"

USING_NS_CC;

ScoreMenu* ScoreMenu::create()
{
    ScoreMenu *pRet = new ScoreMenu();
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

Scene* ScoreMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreMenu::create();
    scene->addChild(layer);
    return scene;
}

void ScoreMenu::initializeMenu() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::createWithSpriteFrameName("bg_score_table.png");
    bg->setScale(0.9);
    bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 90));
    this->addChild(bg, 1);
    
    super::initializeMenu();
    CCLOG("Score");
}


cocos2d::Layer* ScoreMenu::createMenuLayer() {
    return ScoreMenuPopup::create();
}