
#include "GameController.h"

#include "Chef.h"
#include "Conveyor.h"
#include "ScoreLayer.h"
#include "Item.h"
#include "ItemFactory.h"
#include "BonusMenu.h"
#include "MindCloudTips.h"
#include "Pot.h"
#include "MovementController.h"


GameController::GameController(){}

GameController::~GameController() {}

GameController* GameController::createWitLayer(cocos2d::Layer* initWithLayer)
{

   GameController *pRet = new GameController();
   if (pRet && pRet->initWithLayer(initWithLayer))
   {
      pRet->_items = new Vector<cocos2d::Node*>(10);
      return pRet;
   }
   else
   {
      delete pRet;
      pRet = NULL;
      return NULL;
   }
}

bool GameController::initWithLayer(cocos2d::Layer* aGameLayer)
{
   cocos2d::Size visibleSize;
   cocos2d::Vec2 origin;

   _gameLayer = aGameLayer;
   
   visibleSize = Director::getInstance()->getVisibleSize();
   origin = Director::getInstance()->getVisibleOrigin();
   
   this->arrangeBackground(origin,visibleSize);
   this->populateGameObjects(origin,visibleSize);
   
   return true;
}

void GameController::arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{

   Sprite* bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
   bg->setPosition(Vec2(aVisibleSize.width/2 + anOrigin.x, aVisibleSize.height/2 + anOrigin.y));
   _gameLayer->addChild(bg, -1);
   
    BonusMenu* bonusMenu = BonusMenu::create();
    bonusMenu->setPosition(Vec2(bonusMenu->getPosition().x - (aVisibleSize.width/2 + anOrigin.x) + 140, aVisibleSize.height/2 + anOrigin.y - 100));
    _gameLayer->addChild(bonusMenu, 0);
    
    float yOffsetConveyer = 615;
    
    Chef* chef = Chef::create();
    chef->setPosition(Vec2(chef->getPosition().x + 200, yOffsetConveyer)); //TODO: remove x offset position
    chef->setScale(0.5); //TODO: remove scale
    _gameLayer->addChild(chef, 0);
    
   
    MindCloudTips* cloudTips = MindCloudTips::create("tips_level_1.png");
    cloudTips->setPosition(Vec2(140, yOffsetConveyer + 100));
    _gameLayer->addChild(cloudTips, 2);
    cloudTips->toggleTip();
   
    Conveyor* conv = Conveyor::create();
    conv->setPosition(Vec2(0, yOffsetConveyer));
    _gameLayer->addChild(conv, 1);
    
    Pot* pot = Pot::create();
    Node* potBack = pot->getBack();
    _gameLayer->addChild(potBack, 11);
    Node* potFront = pot->getFront();
    _gameLayer->addChild(potFront, 100);
    
    ScoreLayer* scoreLayer = ScoreLayer::create(2300);
    scoreLayer->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 100));
    _gameLayer->addChild(scoreLayer, 1);
    
   
    //_mover = new MovementController();
    //_mover->init();
}

void GameController::populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   // create items array
   // array of arrays (each member stores only one typw of item)?
   
   // add items toarray
   
   // conv shuld have velocity  property
   // get velocity to start moving items
   
 /*
   Hands* hands;
   
   hands = Hands::create(chef->getContentSize().width/2); //TODO: remove divide 2
   hands->setPosition(Vec2(chef->getPosition().x, yOffsetConveyer));
   _gameLayer->addChild(hands, 2);

   Item* item = ItemFactory::createItem(1, 1);
   //Gabbage* foodItem = Gabbage::create();
   item->setPosition(Vec2(aVisibleSize.width + anOrigin.x, -100));
   //conv->addChild(foodItem);
   conv->addChild(item, 10);
  */
}

void startGame()
{

}

void stopGame()
{

}


void GameController::update(float dt)
{
   
   /*
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
    */


}

