
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
#include "UserDataProvider.h"
#include "Garbage.h"
#include "Food.h"
#include "Multiplier.h"
#include "GameOverPopup.h"
#include "SimpleAudioEngine.h"
#include "GameCycleIndicator.h"

#include "time.h"

#define kWallZO 0
#define kConveyurZO 10
#define kItemZO1 20
#define kChefZO 30
#define kCloudZO 40
#define kFloorZO 50
#define kItemZO3 51
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
   _putNextItemDt = 0.0f;
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
   
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic.mp3", true);
    
    _levelInfo = LevelProvider::createForLevel(1);
    _userData = UserDataProvider::create();
    
    float speed = _levelInfo->getSpeed();
    std::vector<int> requiredFroodItems = _levelInfo->getRequiredItems();
    std::vector<int> allowedFoodItems = _levelInfo->getAllowedFoodItems();
    std::vector<int> allowedGarbageItems = _levelInfo->getAllowedGarbageItems();
    
   this->arrangeBackground(origin,visibleSize);
   _itemIdlePos = Vec2(visibleSize.width + 50.0f, _convY + 70.0f);
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
   
    MindCloudTips* cloudTips = MindCloudTips::create(CCString::createWithFormat("tips_level_%i.png", 1)->getCString());
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
    
    _scoreLayer = ScoreLayer::create(_userData->getUserScore());
    _scoreLayer->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 100));
    _gameLayer->addChild(_scoreLayer, kCloudZO);

    _multiplier = Multiplier::create();
    _multiplier->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 60));
    _gameLayer->addChild(_multiplier, kCloudZO);
    
    _gameCycleInd = GameCycleIndicator::createWithGameTime(_levelInfo->getTime());
    _gameCycleInd->setPosition(Vec2(0, _convY - 40));
    _gameLayer->addChild(_gameCycleInd, kCloudZO);
    
    _theChef->startChefBodyAnimation();
   
   _cntPoints->pushBack(ControlPointDef::create(Point(470.0f,300.0f),kControlPointTypePotMargin)); // left floor
   _cntPoints->pushBack(ControlPointDef::create(Point(80.0f,250.0f),kControlPointTypeFloor)); // right floor
   _cntPoints->pushBack(ControlPointDef::create(Point(60.0f,250.0f),kControlPointTypeFloor)); // right floor
   _cntPoints->pushBack(ControlPointDef::create(Point(145.0f,300.0f),kControlPointTypePotMargin)); // margin
   _cntPoints->pushBack(ControlPointDef::create(Point(280.0f,0.0f),kControlPointTypePotCenter)); // center
   _cntPoints->pushBack(ControlPointDef::create(Point(300.0f,0.0f),kControlPointTypePotCenter)); // center
   _cntPoints->pushBack(ControlPointDef::create(Point(540.0f,200.0f),kControlPointTypeFloor)); // floor
   _cntPoints->pushBack(ControlPointDef::create(Point(520.0f,250.0f),kControlPointTypeFloor)); // floor
}

int getRandomNumber(int from ,int to) {
   return (int)from + arc4random() % (to + 1);
}

float getRandomFloat(float from ,float to) {
   // seed the random
   srand (static_cast <unsigned> (time(0)));
   
   return from + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(to-from)));

}

void GameController::populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   Item* item = nullptr;
   
   for (int iItm = 0; iItm < 20; iItm++) {
       item = ItemFactory::createItem(getRandomNumber(0, 1), getRandomNumber(0, 3));
      item->setIdle(_itemIdlePos); //-1 * offset
      
      item->setScale(1.0);
      _gameLayer->addChild(item,kItemZO1);
      _items->pushBack(item);
   }

}

void startGame()
{

}

void GameController::stopGame()
{
    Director::getInstance()->pause();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameController::putIdleItemOnConveyour(float dt, Item* anItem)
{
   Vec2 pos = anItem->getPosition();
   int zOrder = anItem->getLocalZOrder();
	if(_putNextItemDt < 0.0f && pos.x == _itemIdlePos.x && zOrder == kItemZO1){ //
      
      anItem->setLocalZOrder(kItemZO1);
      float actionOffsetX = _itemIdlePos.x + anItem->getContentSize().width + 1;
      Vec2 targetPoint = Vec2(_itemIdlePos.x -  actionOffsetX, _itemIdlePos.y);
      float actionDuration = actionOffsetX/_convVelY;

      FiniteTimeAction* itemAction = anItem->getConveyourAction(actionDuration, targetPoint);
      float scaleFactor = this->getScaleFactor(_itemIdlePos, 0);
      anItem->setScale(scaleFactor);
      anItem->runAction(itemAction);
      
		_putNextItemDt = getRandomNumber(1, 3);
	}

}

void GameController::setItemIdle(float dt, Item* anItem)
{
   anItem->setIdle(_itemIdlePos);
   anItem->setZOrder(kItemZO1);
}

void GameController::runTossActionWithScale(Item* anItem, ControlPointDef* aPointDef, float aDuration, Point anImpulse)
{
   FiniteTimeAction* itemAction = anItem->getTossAction(aDuration,
                                                        aPointDef->_controlPoint,
                                                        aPointDef->_controlPointType,
                                                        anImpulse);
   float scaleFactor = this->getScaleFactor(aPointDef->_controlPoint,aPointDef->_controlPointType);
   
   ScaleTo* scaleAction = ScaleTo::create(aDuration, scaleFactor);
   Spawn* cobinedAction = Spawn::create(itemAction, scaleAction, NULL);
   anItem->setLocalZOrder(kItemZO2);

   anItem->runAction(cobinedAction);
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
      float totalActionDuration = 1.5f;
      this->runTossActionWithScale(anItem, collisionEndPointDef, totalActionDuration, anImpulse);
   }
   
}


void GameController::runBumpAction(Item* anItem)
{
   int currentCollisionType = anItem->_currentTargetType;
   float actionDuration = 0.6f;
   float scaleFactor;
   
   float impulseX = (float)((float)getRandomNumber(0,10))/10.0f;
   float impulseY = (float)((float)getRandomNumber(0,10))/10.0f;
   
   Point impulse = Point(impulseX, impulseY);
   if (currentCollisionType == kControlPointTypePotMargin) {
      actionDuration = 1.2f;
      FiniteTimeAction* itemAction = anItem->getPotEdgeBumpAction(actionDuration, impulse);
      scaleFactor = this->getScaleFactor(anItem->_currentTargetPoint,anItem->_currentTargetType);
      
      ScaleTo* scaleAction = ScaleTo::create(actionDuration, scaleFactor);
      Spawn* cobinedPotBump = Spawn::create(itemAction, scaleAction, NULL);
      anItem->setLocalZOrder(kItemZO2);
      anItem->runAction(cobinedPotBump);
   }else
      if(currentCollisionType == kControlPointTypeFloor){
         FiniteTimeAction* itemAction = anItem->getFloorBumpAction(actionDuration, impulse);
          Sprite* crack = anItem->createCrack();
          if (crack != NULL) {
              crack->setPosition(anItem->getPosition());
              this->_gameLayer->addChild(crack);
              crack->runAction(FadeOut::create(3));
          }
         
         scaleFactor = this->getScaleFactor(anItem->_currentTargetPoint,anItem->_currentTargetType);
         
         ScaleTo* scaleAction = ScaleTo::create(actionDuration, scaleFactor);
         Spawn* cobinedAction = Spawn::create(itemAction, scaleAction, NULL);
         anItem->setLocalZOrder(kItemZO3);
         anItem->runAction(cobinedAction);
   }else
      if (currentCollisionType == kControlPointTypePotCenter){
         anItem->setLocalZOrder(kItemZO3);
          
          this->checkGameProgress(anItem);
      }
}


void GameController::update(float dt)
{
   
   Item* item = nullptr;
   Vec2 itemPos;
   Size itemSize;
   _idxRotated = (_idxRotated + 1) < _items->size() ? (_idxRotated + 1) : 0;
    _gameCycleInd->nextStep(dt);
   
   // set items idle/put them on the conveuir
   for (int i = _idxRotated; i < _items->size(); i++) {
      item = (Item*)_items->at(i);
      this->putIdleItemOnConveyour(dt, item);
   }
   _putNextItemDt -= dt;


   for(Node* nitem : *_items){
      
      item = (Item*)nitem;
      itemPos = item->getPosition();
      itemSize = item->getContentSize();
      
      // item moves behind the screen width
      if(item->getPosition().x + item->getContentSize().width + 10.0 <= Director::getInstance()->getVisibleOrigin().x){
         this->setItemIdle(dt, item);
      }

      // item left on coveyor belt till disappear
      if (itemPos.x  < 0.0f &&
          item->isItemInCurrentTargetPoint() && item->getLocalZOrder() == kItemZO1) {
         this->setItemIdle(dt, item);
      }
      
      if (itemPos.x == _itemIdlePos.x && item->getLocalZOrder() != kItemZO1) {
         this->setItemIdle(dt, item);
      }
      
      if (item->getLocalZOrder() == kItemZO1) { //toss
         //_theChef->setConveyorVelocity(_convVelY);
         //_theChef->chefWathItem(item);
         if (_theChef->tryToCatchItem(item, _convVelY)) {
            //this->throwItemSimple(item,_theChef->getActiveBouncePoint().x,_theChef->getBounceImpulse());
            this->throwItemSimple(item,_theChef->getActiveBouncePoint().x,_theChef->getBounceImpulse());
         }
         this->throwItemSimple(item,_theChef->getActiveBouncePoint().x,_theChef->getBounceImpulse());
         
      } else
      if (item->getLocalZOrder() == kItemZO2 && item->isItemInCurrentTargetPoint()) {
         this->runBumpAction(item);
      } else
         if (item->getLocalZOrder() == kItemZO3 && item->isItemInCurrentTargetPoint()) {
            float actionDuration = 1.0f;
            Point impulse = Point(1.0f,1.0f);
            FiniteTimeAction* itemAction = item->getVanishAction(actionDuration, _itemIdlePos, impulse);
            
            float scaleFactor = this->getScaleFactor(item->_currentTargetPoint,item->_currentTargetType);
            
            ScaleTo* scaleAction = ScaleTo::create(actionDuration, scaleFactor);
            Sequence* cobinedAction = Sequence::create(itemAction, scaleAction, NULL);
            item->runAction(cobinedAction);

         }
      
   }
}

ControlPointDef* GameController::findControlPointDefByAngle(Item* anItem, float angle, float xImpulse) {
   // angle = abs(angle);
    
    int currentTargetType = anItem->_currentTargetType;
    Point currentTargetPoint = anItem->_currentTargetPoint;
    float currentTargetPointX = currentTargetPoint.x;
    
    float offsetX = 0;
    if (xImpulse > 0 && xImpulse < 0.3) {
        offsetX = 40;
    } else if (xImpulse > 0.6) {
        offsetX = 220;
    } else if (xImpulse > 0.8) {
        offsetX = 480;
    }
    
    if (60 < angle && angle < 135 ) { //bottom
        return ControlPointDef::create(Point(280.0f,0.0f), kControlPointTypePotCenter);
    } else if (135 < angle && angle < 180) { //left
        return ControlPointDef::create(Point(60.0f,250.0f), kControlPointTypeFloor);
    } else if (-45 < angle && angle < 60) { //right
        return ControlPointDef::create(Point(520.0f,250.0f),kControlPointTypeFloor);
    } else if (- 180 < angle && angle < -135) { //left
        return ControlPointDef::create(Point(60.0f,250.0f), kControlPointTypeFloor);
    } else { //top
        return ControlPointDef::create(Point(280.0f,0.0f), kControlPointTypePotCenter);
    }
}

void GameController::changeItemPath(Item *anItem, float angle, cocos2d::Vec2 anImpulse)
{
    
   anItem->stopAllActions();
   float actionDuration = 1.5f;
   ControlPointDef* collisionEndPointDef = findControlPointDefByAngle(anItem, angle, anImpulse.x);
   runTossActionWithScale(anItem, collisionEndPointDef, actionDuration, anImpulse);
}

float GameController::getScaleFactor(cocos2d::Point anEndPoint, int aControlPointType)
{
   //float visibleHeight = Director::getInstance()->getVisibleSize().height;
   float floorOffset = aControlPointType < 2 ? 200.0f : 0.0f;
   float scaleFactor = 1.0f;
   float checkPointY = anEndPoint.y + floorOffset;

   if (checkPointY > -100.0f && checkPointY <= 310.0f ) {
      scaleFactor = 2.0f;
   }
   else  if (checkPointY > 310.0f && checkPointY <= 400.0f ) {
      scaleFactor = 0.9f;
   }
   else if (checkPointY > 400.0f && checkPointY <= 500.0f ) {
      scaleFactor = 0.9f;
   }
   else if (checkPointY > 500.0f && checkPointY <= 900.0f ) {
      scaleFactor = 0.7f;
   }

   //float scaleFactor = exp((visibleHeight - (anEndPoint.y + floorOffset))/visibleHeight);
   
   //float scaleFactor = cbrt((visibleHeight - (anEndPoint.y + floorOffset))/visibleHeight);
   //float scaleFactor = acos((visibleHeight - (anEndPoint.y + floorOffset))/visibleHeight);
   //scaleFactor = atan((visibleHeight - (anEndPoint.y + floorOffset))/visibleHeight);
   //float
   //scaleFactor = asin((visibleHeight - checkPointY)/visibleHeight);
   
   //scaleFactor += 0.3f;
   return scaleFactor;
}

void GameController::checkGameProgress(Item* anItem) {
    if (anItem->_itemType == 1) {
        _multiplier->reset();
        this->stopGame(); //TODO:
        //_gameLayer->pause();
        GameOverPopup* goPopup = GameOverPopup::create();
        _gameLayer->addChild(goPopup, 1001);
    } else {
        if (_levelInfo->isRequiredItem(anItem->_itemId)) {
            _scoreLayer->updateScore(10);
            int multiCount = _multiplier->update(anItem->_itemId);
            if (multiCount > 4) {
                _scoreLayer->updateScore(50);
                _multiplier->reset();
            }
        } else {
            //_scoreLayer->updateScore(0);
            _multiplier->reset();
        }
    }
}

