
#include "GameMenu.h"
#include "Chef.h"
#include "Conveyor.h"
#include "ScoreLayer.h"
#include "Item.h"
#include "ItemFactory.h"
#include "BonusMenu.h"
#include "MindCloudTips.h"
#include "Pot.h"
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


int getRandomNumber(int from ,int to) {
    return (int)from + arc4random() % (to-from+1);
}

void GameMenu::initializeMenu() {
    super::initializeMenu();

    CCLOG("Game");
   
   //_theGameController = GameController::createWitLayer(this);
   
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    Sprite* bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);

    BonusMenu* bonusMenu = BonusMenu::create();
    bonusMenu->setPosition(Vec2(bonusMenu->getPosition().x - (visibleSize.width/2 + origin.x) + 140, visibleSize.height/2 + origin.y - 100));
    this->addChild(bonusMenu, 0);
    
    float yOffsetConveyer = 615;
    
    Chef* chef = Chef::create();
    chef->setPosition(Vec2(chef->getPosition().x + 200, yOffsetConveyer)); //TODO: remove x offset position
    chef->setScale(0.5); //TODO: remove scale
    this->addChild(chef, 0);
    
    hands = Hands::create(chef->getContentSize().width/2); //TODO: remove divide 2
    hands->setPosition(Vec2(chef->getPosition().x, yOffsetConveyer));
    this->addChild(hands, 2);
    
    MindCloudTips* cloudTips = MindCloudTips::create("tips_level_1.png");
    //cloudTips->setPosition(Vec2(chef->getPosition().x - cloudTips->getContentSize().width, chef->getPosition().y + chef->getContentSize().height));
    cloudTips->setPosition(Vec2(140, yOffsetConveyer + 100));
    this->addChild(cloudTips, 2);
    cloudTips->toggleTip();
    
    conv = Conveyor::create();
    conv->setPosition(Vec2(0, yOffsetConveyer));
    this->addChild(conv, 1);
    
    yPosStartGrab = conv->getContentSize().width/2;
    yPosCheckGrab = yPosStartGrab + 100;
    
    Item* item = ItemFactory::createItem(1, 1);
    //Gabbage* foodItem = Gabbage::create();
    item->setPosition(Vec2(visibleSize.width + origin.x, -100));
    //conv->addChild(foodItem);
    conv->addChild(item, 10);
    
    Pot* pot = Pot::create();
    Node* potBack = pot->getBack();
    this->addChild(potBack, 11);
    Node* potFront = pot->getFront();
    this->addChild(potFront, 100);
    
    ScoreLayer* scoreLayer = ScoreLayer::create(2300);
    scoreLayer->setPosition(Vec2(500, visibleSize.height + origin.y - 100));
    this->addChild(scoreLayer, 1);
    
    
    lastCreatedItem = 0;
    nextItemDt = getRandomNumber(4, 6);
   
   //_mover = new MovementController();
   //_mover->init();
   
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
       
       _mover->addItem(*item);
       
        lastCreatedItem = 0;
        nextItemDt = getRandomNumber(4, 6);
    } else {
        lastCreatedItem +=dt;
    }
   
   _mover->update(dt);
    
    // grab detecting loop part
    float yPosFirstItem = conv->getFirstItemPosY();
    if (yPosFirstItem >= yPosStartGrab) {
        //hands->startGrab();
    } else if (yPosFirstItem >= yPosCheckGrab) {
        //hands->preGrab(conv->getFirst);
    }
}