
#include "GameMenu.h"
#include "Chef.h"

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    Chef* chef = Chef::create();
    chef->setPosition(Vec2(chef->getPosition().x + 50, 315)); //TODO: remove x position
    this->addChild(chef, 0);
    
    //TODO: move to seporate component
    conveyorNode = ParallaxNode::create(); //1
    this->addChild(conveyorNode, 1);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    Vec2 speed = Vec2(0.05, 0.05);
    conveyor1 = Sprite::createWithSpriteFrameName("conveyer_1.png");
    conveyor2 = Sprite::createWithSpriteFrameName("conveyer_1.png");
    
    conveyorNode->addChild(conveyor1, 0, speed, Vec2(0, 316-conveyor1->getContentSize().height/2));
    conveyorNode->addChild(conveyor2, 0, speed, Vec2(conveyor2->getContentSize().width - 1, 316-conveyor2->getContentSize().height/2));

    this->scheduleUpdate();
}

void GameMenu::update(float dt) {
    Vec2 pos1 = conveyor1->getPosition();
    Vec2 pos2 = conveyor2->getPosition();
    
    pos1.x -= 5.0f;
    pos2.x -= 5.0f;
    
    
    
    if(pos1.x <=-(visibleSize.width*0.5f) )
    {
        pos1.x = pos2.x + visibleSize.width;
    }
    
    if(pos2.x <=-(visibleSize.width*0.5f) )
    {
        pos2.x = pos1.x + visibleSize.width;
    }
    
    conveyor1->setPosition(pos1);
    conveyor2->setPosition(pos2);
    
    //Vec2 backgroundScrollVert = Vec2(-100, 0);
    //conveyorNode->setPosition(conveyorNode->getPosition() + backgroundScrollVert *dt);
}