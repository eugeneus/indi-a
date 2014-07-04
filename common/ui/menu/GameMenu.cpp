
#include "GameMenu.h"
#include "Chef.h"
#include "Conveyor.h"
#include "ScoreLayer.h"
#include "Item.h"
#include "ItemFactory.h"

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


int getRandomNumber(int from ,int to) {
    return (int)from + arc4random() % (to-from+1);
}

void GameMenu::initializeMenu() {
    super::initializeMenu();

    CCLOG("Game");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    Sprite* bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    Chef* chef = Chef::create();
    chef->setPosition(Vec2(chef->getPosition().x + 50, 315)); //TODO: remove x position
    this->addChild(chef, 0);
    
    hands = Hands::create(chef->getContentSize().width);
    hands->setPosition(Vec2(chef->getPosition().x, chef->getPosition().y));
    this->addChild(hands, 2);
    
    
    conv = Conveyor::create();
    conv->setPosition(Vec2(0, 315));
    this->addChild(conv, 1);
    
    yPosStartGrab = conv->getContentSize().width/2;
    yPosCheckGrab = yPosStartGrab + 100;
    
    Item* item = ItemFactory::createItem(1, 1);
    //Gabbage* foodItem = Gabbage::create();
    item->setPosition(Vec2(visibleSize.width + origin.x, -100));
    //conv->addChild(foodItem);
    conv->addChild(item, 10);
    
    ScoreLayer* scoreLayer = ScoreLayer::create(2300);
    scoreLayer->setPosition(Vec2(500, visibleSize.height + origin.y - 100));
    this->addChild(scoreLayer, 1);
    
    
    lastCreatedItem = 0;
    nextItemDt = getRandomNumber(4, 6);
    this->scheduleUpdate();
    
}

void GameMenu::update(float dt) {
    
    // generation items loop part
    if (lastCreatedItem >= nextItemDt) {
        int posOffset = getRandomNumber(1, 3);
        int offset = posOffset == 1 ? 20 : (posOffset == 2 ? 50 : 100);
        Item* item = ItemFactory::createItem(getRandomNumber(0, 1), getRandomNumber(0, 1));
        item->setPosition(Vec2(visibleSize.width + origin.x, -1 * offset));
        conv->addChild(item, 10);
        
        lastCreatedItem = 0;
        nextItemDt = getRandomNumber(4, 6);
    } else {
        lastCreatedItem +=dt;
    }
    
    // grab detecting loop part
    float yPosFirstItem = conv->getFirstItemPosY();
    if (yPosFirstItem >= yPosStartGrab) {
        //hands->startGrab();
    } else if (yPosFirstItem >= yPosCheckGrab) {
        //hands->preGrab(conv->getFirst);
    }
}