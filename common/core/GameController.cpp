
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
#include "LevelProvider.h"

#define kWallZO 0
#define kConveyurZO 10
#define kItemZO1 20
#define kChefZO 30
#define kCloudZO 40
#define kFloorZO 50
#define kPotBackZO 60
#define kItemZO2 70
#define kPotFrontZO 80

#define kControlPointTypeFloor 1
#define kControlPointTypePotMargin 2
#define kControlPointTypePotCenter 3

GameController::GameController()
{
   _convY = 0.0f;
   _convVelY = 0.0f;
   _convLegth = 0.0f;
   _putNextItemDt = 2.0f;
   _idxRotated = 0;
   
   _items = new Vector<cocos2d::Node*>(10);
   _cntPoints = new Vector<ControlPointDef*>(10);

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
   
    _levelInfo = LevelProvider::createForLevel(1);
    float speed = _levelInfo->getSpeed();
    std::vector<int> requiredFroodItems = _levelInfo->getRequiredItems();
    std::vector<int> allowedFoodItems = _levelInfo->getAllowedFoodItems();
    std::vector<int> allowedGarbageItems = _levelInfo->getAllowedGarbageItems();
    
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
   
   _cntPoints->pushBack(ControlPointDef::create(Point(480.0f,220.0f),kControlPointTypePotMargin)); // left floor
   _cntPoints->pushBack(ControlPointDef::create(Point(80.0f,200.0f),kControlPointTypeFloor)); // right floor
   _cntPoints->pushBack(ControlPointDef::create(Point(60.0f,250.0f),kControlPointTypeFloor)); // right floor
   _cntPoints->pushBack(ControlPointDef::create(Point(120.0f,200.0f),kControlPointTypePotMargin)); // margin
   _cntPoints->pushBack(ControlPointDef::create(Point(280.0f,0.0f),kControlPointTypePotCenter)); // center
   _cntPoints->pushBack(ControlPointDef::create(Point(300.0f,0.0f),kControlPointTypePotCenter)); // center
   _cntPoints->pushBack(ControlPointDef::create(Point(540.0f,200.0f),kControlPointTypeFloor)); // floor
   _cntPoints->pushBack(ControlPointDef::create(Point(520.0f,250.0f),kControlPointTypeFloor)); // floor
}

int getRandomNumber(int from ,int to) {
   return (int)from + arc4random() % (to-from+1);
}

void GameController::populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   Item* item = nullptr;
   
   for (int iItm = 0; iItm < 10; iItm++) {
      item = ItemFactory::createItem(getRandomNumber(0, 1), getRandomNumber(0, 1));
      item->setIdle(_itemIdlePos); //-1 * offset
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
	if(_putNextItemDt < 0 && pos.x == _itemIdlePos.x && anItem->getLocalZOrder() == kItemZO1){
      
      this->startLinearMove(anItem);
		_putNextItemDt = getRandomNumber(1.9, 2.5);
	}
   
   
}

void GameController::setItemIdle(float dt, Item* anItem)
{
   anItem->setIdle(_itemIdlePos);
   anItem->setZOrder(kItemZO1);
}
void GameController::throwItemSimple(Item* anItem, float throwX, Vec2 anImpulse)
{
   float xThrow = throwX;
   Point ptItem = anItem->getPosition();
   
   if (ptItem.x >= xThrow &&
       ptItem.x <= xThrow + 10.0f &&
       ptItem.y >= _itemIdlePos.y - 20.0f &&
       ptItem.y <= _itemIdlePos.y + 20.0f &&
       anItem->getLocalZOrder() == kItemZO1
       )
   {
      ControlPointDef* collisionEndPointDef = nullptr;
      if (_cntPoints->size() > 0) {
         int randomPointIdx = getRandomNumber(0,(_cntPoints->size()-1));
         collisionEndPointDef = _cntPoints->at(randomPointIdx);
       }
      float totalActionDuration = 3.0f;
      anItem->runBounceAction(totalActionDuration,
                              collisionEndPointDef->_controlPoint,
                              anImpulse,
                              collisionEndPointDef->_controlPointType);
      anItem->setLocalZOrder(kItemZO2);
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
      this->tryPutNextItem(dt, item);
   }
   _putNextItemDt -= dt;


   // do not want to let item fall out of screen, lef and right
   // TODO: adjust bounce so that any trajectory does not lead out of screen
   
   for(Node* nitem : *_items){
      
      item = (Item*)nitem;
      itemPos = item->getPosition();
      itemSize = item->getContentSize();
      if(item->getPosition().x + item->getContentSize().width + 10.0 <= Director::getInstance()->getVisibleOrigin().x){
         this->setItemIdle(dt, item);
      }

      if ((itemPos.x + item->getContentSize().width + 10.0f) < 0.0) {
         this->setItemIdle(dt, item);
      }
      
      if (itemPos.x == _itemIdlePos.x && item->getLocalZOrder() != kItemZO1) {
         this->setItemIdle(dt, item);
      }
      
      if (item->getLocalZOrder() == kItemZO1) {
         _theChef->chefWathItem(item);
         this->throwItemSimple(item,_theChef->getActiveBouncePoint().x,_theChef->getBounceImpulse());
      }
   }
}

ControlPointDef* GameController::findControlPointDefByAngle(float angle) {
    angle = abs(angle);
    if (0 < angle && angle < 46 ) {
        return ControlPointDef::create(Point(520.0f,250.0f),kControlPointTypeFloor); //right
    } else if (135 < angle && angle < 225) {
        return ControlPointDef::create(Point(60.0f,250.0f), kControlPointTypeFloor); //left
    } else {
        return ControlPointDef::create(Point(280.0f,0.0f), kControlPointTypePotCenter);
    }
}

void GameController::changeItemPath(Item *anItem, float angle, cocos2d::Vec2 anImpulse) {
    //throwItemSimple(anItem, throwX, anImpulse);
    anItem->stopAllActions();
    //anItem->setZOrder(kItemZO2);
    ControlPointDef* collisionEndPointDef = findControlPointDefByAngle(angle);
    anItem->runTouchAction(0.5, collisionEndPointDef->_controlPoint,
                           anImpulse,
                           collisionEndPointDef->_controlPointType);
}

