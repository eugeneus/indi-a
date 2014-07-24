
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

#define kWallZO 0
#define kConveyurZO 10
#define kItemZO1 20
#define kChefZO 30
#define kCloudZO 40
#define kFloorZO 50
#define kPotBackZO 60
#define kItemZO2 70
#define kPotFrontZO 80


GameController::GameController()
{
   _convY = 0.0f;
   _convVelY = 0.0f;
   _convLegth = 0.0f;
   _putNextItemDt = 2.0f;
   _idxRotated = 0;
   
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
   _itemIdlePos = Vec2(visibleSize.width, _convY + 40.0f);
   this->populateGameObjects(origin,visibleSize);
   

   
   return true;
}

void GameController::arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   
   SpriteFrameCache* cache = SpriteFrameCache::getInstance();
   cache->addSpriteFramesWithFile("images.plist");

   Sprite* bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
   bg->setPosition(Vec2(aVisibleSize.width/2 + anOrigin.x, aVisibleSize.height/2 + anOrigin.y));
   _gameLayer->addChild(bg, kWallZO);
   
    BonusMenu* bonusMenu = BonusMenu::create();
    bonusMenu->setPosition(Vec2(bonusMenu->getPosition().x - (aVisibleSize.width/2 + anOrigin.x) + 140, aVisibleSize.height/2 + anOrigin.y - 100));
    _gameLayer->addChild(bonusMenu, kWallZO);
    
    float yOffsetConveyer = 615;
    
   _theChef = Chef::create(_gameLayer, kChefZO);
   Size chefSize = _theChef->getSize();
   Point chefOrigin = Point((aVisibleSize.width - (chefSize.width))/2.0f, yOffsetConveyer);
   _theChef->setOrigin(chefOrigin);
   
    MindCloudTips* cloudTips = MindCloudTips::create("tips_level_1.png");
    cloudTips->setPosition(Vec2(140, yOffsetConveyer + 100));
    _gameLayer->addChild(cloudTips, kCloudZO);
    cloudTips->toggleTip();
   
    _convY = yOffsetConveyer - 102;
    _convVelY = 50;
    _convLegth = aVisibleSize.width;

    Conveyor* conv = Conveyor::create(_convVelY, _convLegth);
   conv->setPosition(Vec2(0, _convY));
    _gameLayer->addChild(conv, kConveyurZO);
    
    _thePot = Pot::create(_gameLayer,kPotFrontZO,kPotBackZO);
   Size sz = _thePot->getFrontRect().size;
   Point potOrigin = Point(0,0);//Point(aVisibleSize.width/2.0f - sz.width/2.0f, 0.0f);
   _thePot->setOriginPos(potOrigin);
    ScoreLayer* scoreLayer = ScoreLayer::create(2300);
    scoreLayer->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 100));

    _theChef->startChefBodyAnimation();
   
   _points = PointArray::create(7);
   _points->retain();
   _points->addControlPoint(Vec2(480.0f,220.0f)); // left pot
   _points->addControlPoint(Vec2(80.0f,200.0f)); // right floor
   _points->addControlPoint(Vec2(60.0f,250.0f)); // right floor
   _points->addControlPoint(Vec2(120.0f,200.0f)); // right pot
   _points->addControlPoint(Vec2(280.0f,0.0f)); // about center pot
   _points->addControlPoint(Vec2(300.0f,0.0f)); // about center pot
   _points->addControlPoint(Vec2(540.0f,200.0f)); // right floor
   _points->addControlPoint(Vec2(520.0f,250.0f)); // right floor
   
   
   
}

int getRandomNumber(int from ,int to) {
   return (int)from + arc4random() % (to-from+1);
}

void GameController::populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   Item* item = nullptr;
   
   for (int iItm = 0; iItm < 10; iItm++) {
      item = ItemFactory::createItem(getRandomNumber(0, 1), getRandomNumber(0, 1));
      item->setPosition(_itemIdlePos); //-1 * offset
      item->setScale(0.7);
      _gameLayer->addChild(item,kItemZO1);
      _items->pushBack(item);
   }

}

void startGame()
{

}

void stopGame()
{

}


void GameController::startLinearMove(Item* anItem)
{
   anItem->setLocalZOrder(kItemZO1);
   float actionOffsetX = _itemIdlePos.x + anItem->getContentSize().width + 1;
   Vec2 targetPoint = Vec2(_itemIdlePos.x -  actionOffsetX, _itemIdlePos.y);
   
	float actionDuration = actionOffsetX/_convVelY;
   
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
		_putNextItemDt = getRandomNumber(1.5, 2.5);
	}
   
   
}

void GameController::setItemIdle(float dt, Item* anItem)
{
   
   anItem->stopAllActions();
   anItem->setPosition(_itemIdlePos);
   anItem->setDefaultSize();
   anItem->setZOrder(kItemZO1);

}

// based on impulse
ccBezierConfig bezierConfigBouncePathForParams(Item* anItem, float aWeight, Vec2 anImpulse)
{
   ccBezierConfig bezier;

   //TODO: calculate initial bezier parameters based on visible screen size,
   //      so that even with impulce (1,1) item fall into screen area
   Size visibleSize = Director::getInstance()->getVisibleSize();
   Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
   Point itemPos = anItem->getPosition();
   Point cp1 = itemPos;
   Point cp2 = itemPos;
   Point endPoint = itemPos;
   
   // assume start point of impulse always (0,0)
   cp1.y = cp1.y + ((visibleSize.height) * anImpulse.y);
   cp1.x = cp1.x + ((visibleSize.width - cp1.x) * anImpulse.x);
   
   endPoint.y = endPoint.y - (endPoint.y * anImpulse.y);
   endPoint.x = endPoint.x + ((visibleSize.width - cp1.x) * anImpulse.x);  //the same as cp1 x
   
   cp2 = endPoint;
   
   bezier.controlPoint_1 = cp1;
   bezier.controlPoint_2 = cp2;
   bezier.endPosition = endPoint;
   
   return bezier;

}

// based on predefined end points
ccBezierConfig bezierConfigBouncePathToEndPoint(Point anEndPoint, Item* anItem, float aWeight, Vec2 anImpulse)
{
   ccBezierConfig bezier;
   
   Size visibleSize = Director::getInstance()->getVisibleSize();
   Point visibleOrigin = Director::getInstance()->getVisibleOrigin();
   Point itemPos = anItem->getPosition();
   Point cp1 = itemPos;
   
   // assume start point of impulse always (0,0)
   cp1.y = itemPos.y + ((visibleSize.height) * anImpulse.y);
   cp1.x = itemPos.x + ((anEndPoint.x - itemPos.x) * anImpulse.x);
   
   bezier.controlPoint_1 = cp1;
   bezier.controlPoint_2 = anEndPoint;
   bezier.endPosition = anEndPoint;
   
   return bezier;
   
}


FiniteTimeAction* GameController::bounceItemAction(Item* anItem, float aWeight, Vec2 anImpulse)
{
   
   Point endPoint = Point(0.0f, 100.0f);
   if (_points->count() > 0) {
      int randomPointIdx = getRandomNumber(0,(_points->count()-1));
      endPoint = _points->getControlPointAtIndex(randomPointIdx);
   }
 
   ccBezierConfig bouncePathConfig = bezierConfigBouncePathToEndPoint(endPoint,anItem, aWeight, anImpulse);
   
   float actionDuration = 3; //TODO: chould be calculated based on impulse and weight
   
   BezierTo* bounceAction = BezierTo::create(actionDuration, bouncePathConfig);
   bounceAction->setTag(1);
   
   FiniteTimeAction* itemFallAction = anItem->getFloorBumpAction(1.0, endPoint, anImpulse);
   
   FiniteTimeAction* finalAction = nullptr;

   if (itemFallAction) {
      finalAction = Sequence::create(bounceAction,itemFallAction,NULL);
   }
   else{
      finalAction = Sequence::create(bounceAction, NULL);
   }
  
   return finalAction;
}

void GameController::throwItemSimple(Item* anItem, float throwX, Vec2 anImpulse)
{
   float xThrow = throwX;
   Point ptItem = anItem->getPosition();
   
   //
   
   if (ptItem.x >= xThrow &&
       ptItem.x <= xThrow + 10.0f &&
       ptItem.y >= _itemIdlePos.y - 20.0f &&
       ptItem.y <= _itemIdlePos.y + 20.0f &&
       anItem->getLocalZOrder() == kItemZO1
       ){
     
      anItem->setLocalZOrder(kItemZO2);
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
   
   // set items idle/put them on the conveuir
   for (int i = _idxRotated; i < _items->size(); i++) {
      item = (Item*)_items->at(i);
      if(item->getPosition().x + item->getContentSize().width + 1 <= Director::getInstance()->getVisibleOrigin().x){
         this->setItemIdle(dt, item);
      }
      this->tryPutNextItem(dt, item);
   }
   _putNextItemDt -= dt;


   // do not want to let item fall out of screen, lef and right
   // TODO: adjust bounce so that any trajectory does not lead out of screen
   
   for(Node* nitem : *_items){
      
      item = (Item*)nitem;
      itemPos = item->getPosition();
      itemSize = item->getContentSize();
      if (itemPos.x < 0.0) { //+ itemSize.width + 1
         this->setItemIdle(dt, item);
         item->setZOrder(kItemZO1);
      }
      
      if (item->getLocalZOrder() == kItemZO1) {
         _theChef->chefWathItem(item);
         this->throwItemSimple(item,_theChef->getActiveBouncePoint().x,_theChef->getBounceImpulse());
      }
   }
}

