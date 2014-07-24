
#include "GameMenu.h"
#include "MovementController.h"
#include "GameController.h"
#include "TouchController.h"
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
    _touchController = TouchController::createWithLayer(this);
    
    // listen for touch events
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameMenu::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameMenu::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameMenu::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameMenu::onTouchesCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
   
    this->scheduleUpdate();
   
}

void GameMenu::update(float dt) {
   
   this->_theGameController->update(dt);
}

GameController* GameMenu::getGameController() {
    return _theGameController;
}

void GameMenu::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) {
    CCLOG("touch onTouchesBegan");
    _touchController->onTouchesBegan(touches, unused_event);
}

void GameMenu::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) {
    CCLOG("touch onTouchesMoved");
    _touchController->onTouchesMoved(touches, unused_event);
}

void GameMenu::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) {
    CCLOG("touch onTouchesEnded");
    _touchController->onTouchesEnded(touches, unused_event);
}

void GameMenu::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event) {
    CCLOG("touch onTouchesCancelled");
    _touchController->onTouchesCancelled(touches, unused_event);
}
