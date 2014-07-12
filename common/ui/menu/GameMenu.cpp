
#include "GameMenu.h"
#include "MovementController.h"
#include "GameController.h"
//#include "gl.h"

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

void GameMenu::draw(cocos2d::Renderer* renderer, const kmMat4& transform, bool transformUpdated)
{
   //glColor4f(0.8, 1.0, 0.76, 1.0);
   glLineWidth(2);
   //glEnable(GL_LINE_SMOOTH);
   cocos2d::DrawPrimitives::drawCubicBezier(Point(205,615),Point(250,715),Point(300,600),Point(350,500), 1000);

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
