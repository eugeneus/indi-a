
#include "GameMenu.h"
#include "MovementController.h"
#include "GameController.h"

USING_NS_CC;

GameMenu* GameMenu::create()
{
    GameMenu *pRet = new GameMenu();
    if (pRet && pRet->init("Game"))
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

Scene* GameMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = GameMenu::create();
    scene->addChild(layer);
    return scene;
}

void GameMenu::initializeMenu() {
    super::initializeMenu();

    CCLOG("Game");
   
   _theGameController = GameController::createWitLayer(this);
   
    this->scheduleUpdate();
   
}

void GameMenu::update(float dt) {
   
   this->_theGameController->update(dt);
}
