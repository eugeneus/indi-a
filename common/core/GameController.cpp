
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


GameController::GameController()
{
   _convY = 0.0f;
   _convVelY = 0.0f;

   _convY = 0.0f;
   _convVelY = 0.0f;
   _convLegth = 0.0f;
   
   _putNextItemDt = 2.0f;
   _idxRotated = 0;
   _impulse = Vec2(1.0f,1.0f);
   
   _items = new Vector<cocos2d::Node*>(10);

}

GameController::~GameController() {}

GameController* GameController::createWitLayer(cocos2d::Layer* initWithLayer)
{

   GameController *pRet = new GameController();
   if (pRet && pRet->initWithLayer(initWithLayer))
   {
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
   _itemIdlePos = Vec2(visibleSize.width, _convY);
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
   
    _convY = yOffsetConveyer - 102;
    _convVelY = 50;
    _convLegth = aVisibleSize.width;

    Conveyor* conv = Conveyor::create(_convVelY, _convLegth);
   conv->setPosition(Vec2(0, _convY));
    _gameLayer->addChild(conv, 1);
    
    Pot* pot = Pot::create();
    Node* potBack = pot->getBack();
    _gameLayer->addChild(potBack, 11);
    Node* potFront = pot->getFront();
    _gameLayer->addChild(potFront, 100);
    
    ScoreLayer* scoreLayer = ScoreLayer::create(2300);
    scoreLayer->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 100));
    //_gameLayer->addChild(scoreLayer, 1);
    
   
    //_mover = new MovementController();
    //_mover->init();
}

int getRandomNumber(int from ,int to) {
   return (int)from + arc4random() % (to-from+1);
}

void GameController::populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   Item* item = nullptr;
   
   //float tmp = _items->size();
   //Vec2 itemPos = Vec2(anOrigin.x, _convY);
   
   //Vec2 itemPos = Vec2(aVisibleSize.width/2.0f + anOrigin.x, anOrigin.y + 100);
   
   for (int iItm = 0; iItm < 10; iItm++) {
      item = ItemFactory::createItem(getRandomNumber(0, 1), getRandomNumber(0, 1));
      item->setPosition(_itemIdlePos); //-1 * offset
      item->setScale(0.7);
      _gameLayer->addChild(item,10);
      _items->pushBack(item);
   }
   

   
   
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


void GameController::startLinearMove(Item* anItem)
{
   float actionOffsetX = _itemIdlePos.x + anItem->getContentSize().width + 1;
   Vec2 targetPoint = Vec2(_itemIdlePos.x -  actionOffsetX, _itemIdlePos.y);
   
	float actionDuration = actionOffsetX/_convVelY; // todo correct velocity of conv/items
   
	FiniteTimeAction* actionMove = MoveTo::create(actionDuration,targetPoint);
	// add action to
   actionMove->setTag(1001);
	anItem->runAction(actionMove);
   
}

void GameController::tryPutNextItem(float dt, Item* anItem)
{
   Vec2 pos = anItem->getPosition();
	if(_putNextItemDt < 0 && pos.x == _itemIdlePos.x){
      this->startLinearMove(anItem);
		_putNextItemDt = getRandomNumber(3, 6);
	}
   
   
}

void GameController::setItemIdle(float dt, Item* anItem)
{
	if(anItem->getPosition().x + anItem->getContentSize().width + 1 <= Director::getInstance()->getVisibleOrigin().x){
		
		anItem->setPosition(_itemIdlePos);
	}
   
   
}

void GameController::wipeItems()
{
   //anItem->setPosition(_itemIdlePos);
}

BezierTo* GameController::createBezierPath(Vec2 aStartPos)
{
   ccBezierConfig bezier;
   
   bezier.controlPoint_1 = Point(aStartPos.x + 50.0f, aStartPos.y + 150.0f); //aStartPos.y + 20
   bezier.controlPoint_2 = Point(aStartPos.x + 100.0f, aStartPos.y + 150.0f); //aStartPos.y + 20
   bezier.endPosition = Point(aStartPos.x + 120.0f,aStartPos.y - 150.0f); //730.0f
   
   
   return BezierTo::create(3, bezier);
   
}

BezierTo* GameController::createBezierPath(Vec2 aStartPos, float aWeight, Vec2 anImpulse)
{
   ccBezierConfig bezier;
   
   bezier.controlPoint_1 = Point(aStartPos.x + 50.0f, aStartPos.y + 150.0f); //aStartPos.y + 20
   bezier.controlPoint_2 = Point(aStartPos.x + 100.0f, aStartPos.y + 150.0f); //aStartPos.y + 20
   bezier.endPosition = Point(aStartPos.x + 120.0f,aStartPos.y - 150.0f); //730.0f
   
   return BezierTo::create(3, bezier);
}

ccBezierConfig bezierConfigBouncePathForParams(Item* anItem, float aWeight, Vec2 anImpulse)
{
   ccBezierConfig bezier;

   Point itemPos = anItem->getPosition();
   Point cp1 = itemPos;
   Point cp2 = itemPos;
   Point endPoint = itemPos;
   Size visibleSize = Director::sharedDirector()->getVisibleSize();
   
   cp1.y = cp1.y + ((visibleSize.height - cp1.y) * anImpulse.y);
   cp1.x = cp1.x + ((visibleSize.width - cp1.x) * anImpulse.x);
   
   endPoint.y = endPoint.y - (endPoint.y * anImpulse.y);
   endPoint.x = endPoint.x + ((visibleSize.width - cp1.x) * anImpulse.x);  //the same as cp1 x
   
   cp2 = endPoint;
   
   bezier.controlPoint_1 = cp1;
   bezier.controlPoint_2 = cp2;
   bezier.endPosition = endPoint;
   
   return bezier;

}

BezierTo* GameController::bounceItemAction(Item* anItem, float aWeight, Vec2 anImpulse)
{
   
   ccBezierConfig bouncePathConfig = bezierConfigBouncePathForParams(anItem, aWeight, anImpulse);
   
   float actionDuration = 3; //TODO: chould be calculated based on impulse and weight
   
   BezierTo* bounceAction = BezierTo::create(actionDuration, bouncePathConfig);
   
   return bounceAction;
}

void GameController::throwItemSimple(Item* anItem, Vec2 anImpulse)
{
   float xThrow = 200.0f;
   Point ptItem = anItem->getPosition();
   
   if (ptItem.x >= xThrow &&
       ptItem.x <= xThrow + 3.0f &&
       ptItem.y >= _itemIdlePos.y - 20.0f &&
       ptItem.y <= _itemIdlePos.y + 20.0f
       ){
      
      //CCLOG("Item Pos %f")
      
      FiniteTimeAction* actionBezier = this->bounceItemAction(anItem, 1.0f, anImpulse);
      FiniteTimeAction* actionRotate = nullptr; // plaseholder rotate
      
      FiniteTimeAction* actionMoveTo = nullptr; // plaseholder for floor action
      FiniteTimeAction* actionDelay = DelayTime::create(2);
      FiniteTimeAction* actionPlase = Place::create(_itemIdlePos);
      FiniteTimeAction* scaleBy1 = cocos2d::ScaleBy::create(2.5, 2.5f);
      FiniteTimeAction* scaleRev1 = scaleBy1->reverse();
      FiniteTimeAction* scaleBy2 = cocos2d::ScaleBy::create(0.5, 0.8f);
      FiniteTimeAction* scaleRev2 = scaleBy2->reverse();
      scaleRev1->setDuration(0.1);
      scaleRev2->setDuration(0.1);
      
      anItem->stopActionByTag(1001);
      
      //actionMoveBy =
      //CCMoveBy::create(actionDuration,Vec2(-actionLength, 0.0f));
      //v = Vec2(nSprite->getPosition().x,nSprite->getPosition().y);
      
      anItem->runAction(Sequence::create(actionBezier,
                                          actionDelay,
                                          actionPlase,
                                          //scaleRev1,
                                                               NULL));
      // number of simultaneous actions
      anItem->runAction(Sequence::create(scaleBy1,scaleBy2,scaleRev1,scaleRev2,NULL));
      // rotate
      // screw
      
   }
   
}


void GameController::update(float dt)
{
   
   Item* item = nullptr;
   Vec2 itemPos;
   Size itemSize;
   _idxRotated = (_idxRotated + 1) < _items->size() ? (_idxRotated + 1) : 0;
   
   for (int i = _idxRotated; i < _items->size(); i++) {
      item = (Item*)_items->at(i);
      this->setItemIdle(dt, item);
      this->tryPutNextItem(dt, item);
      
   }
   
   for(Node* nitem : *_items){
      item = (Item*)nitem;
      this->throwItemSimple(item,_impulse);
      
      _impulse.x -= 0.05f;
      _impulse.x  = _impulse.x > -1.0 ? _impulse.x : 1.0f;
   }
   _putNextItemDt -= dt;


}

