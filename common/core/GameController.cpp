
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
#include "GameCompletePopup.h"
#include "SimpleAudioEngine.h"
#include "GameCycleIndicator.h"
#include "BonusMenu.h"
#include "FoodFactory.h"
#include "SoundsConstants.h"
#include "ItemsPool.h"
#include "DishFactory.h"
#include "Dish.h"

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
   _convLegth = 0.0f;
   _putNextItemDt = 0.0f;
   _idxRotated = 0;
    _bonusTimer = 0.0f;
    _elasedTest = 0.0f;
   
   //_items = new Vector<Item*>(10);
   _cntPoints = new Vector<ControlPointDef*>(10);
    _requiredItemTimer = 0.0f;
    _dishFactory = nullptr;
    _mainCource = nullptr;
    _itemsPool =  nullptr;
    _cloudTips = nullptr;
    _isControllerWaitingStop = false;
    _nRound = 1;

    _maxBandVelosity = 100;
    
    _maxRepeatIngridients = 3;
    
    _maxRepeatBonus1 = 3;
    
    _maxRepeatBonus2 = 3;
    
    _maxRepeatBonus3 = 3;
    
    _maxGarbagePct = 0.7;

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
   _gameLayer = aGameLayer;
   
   
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(SOUND_BG, true);
   
    this->setUpInit(true);
    
   return true;
}

void GameController::setUpInit(bool isStart) {
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    int level = 1;
    /*
    if(!isStart) {
        level = _levelInfo->getLevelId() + 1;
        // TODO: remove next lines
        if (level > 3) level = 1;
    }
    */
    
    _levelInfo = LevelProvider::createForLevel(level);
    
    //std::vector<int> requiredFroodItems = _levelInfo->getRequiredItems();
    //std::vector<int> allowedFoodItems = _levelInfo->getAllowedFoodItems();
    //std::vector<int> allowedGarbageItems = _levelInfo->getAllowedGarbageItems();
    _currGameTime = 0.0;
    
    if (isStart)
        this->arrangeBackground(origin,visibleSize);
    else
        releaseAll(origin,visibleSize);
    
    _itemIdlePos = Vec2(visibleSize.width + 40.0f, _convY + 70.0f);
    
    if (!_dishFactory) {
        _dishFactory = DishFactory::create("dishes.plist");
    }
    if (_mainCource) {
        delete _mainCource;
        _mainCource = nullptr;
        
    }
    _mainCource = _dishFactory->getRandomDish();
    
    if (!_cloudTips) {
        const std::string& str = _mainCource->getImageName();
        _cloudTips = MindCloudTips::create(str);
        _gameLayer->addChild(_cloudTips, kCloudZO);
        _cloudTips->toggleTip();
    }
    const std::string& str = _mainCource->getImageName();
    _cloudTips->changeTip(str);
    _cloudTips->setPosition(_cloudTipsPos);
    
    if (!_itemsPool) {
        _itemsPool = ItemsPool::create(_levelInfo,
                                       _maxGarbagePct,
                                       _maxRepeatIngridients,
                                       _maxRepeatBonus1,
                                       _maxRepeatBonus2,
                                       _maxRepeatBonus3
                                       );
    }
    _itemsPool->resetForNewRound(_nRound, _itemIdlePos, _mainCource);
    
}

void GameController::releaseAll(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize) {
    
    std::string bgFrameName = _levelInfo->getBgSpriteFrameName();
    bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgFrameName));
    
    const std::string& str = _mainCource->getImageName();
    _cloudTips->changeTip(str);
    
    float yOffsetConveyer = 615;
    
    _convY = yOffsetConveyer - 102;
    //_bandVelosity = 100;
    _convLegth = aVisibleSize.width;
    
    _bonusMenu->resetActiveBonus();
    _gameCycleInd->setGameTime(_levelInfo->getRoundTime());
    _gameCycleInd->restart();

    _theChef->restartChef();
    _conv->changeCyclingSpeed(_bandVelosity);
    
    for(Item* nitem : _items){
        nitem->removeFromParentAndCleanup(true);
    }
    
    _caughtItemsIds.clear();
    _items.clear();
}

void GameController::arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize)
{
   this->updatePerformanceMetrics();
    
   SpriteFrameCache* cache = SpriteFrameCache::getInstance();
   cache->addSpriteFramesWithFile("images.plist");

   bg = Sprite::createWithSpriteFrameName("level_1_bg.png");
   bg->setPosition(Vec2(aVisibleSize.width/2 + anOrigin.x, aVisibleSize.height/2 + anOrigin.y));
   _gameLayer->addChild(bg, kWallZO);
   
    _bonusMenu = BonusMenu::create(this->_levelInfo);
    _bonusMenu->setPosition(Vec2(_bonusMenu->getPosition().x - (aVisibleSize.width/2 + anOrigin.x) + 140, aVisibleSize.height/2 + anOrigin.y - 80));
    _gameLayer->addChild(_bonusMenu, kWallZO);
    
    float yOffsetConveyer = 615;
    
   _theChef = Chef::create(_gameLayer, kChefZO);
   Size chefSize = _theChef->getSize();
   Point chefOrigin = Point((aVisibleSize.width - (chefSize.width))/2.0f, yOffsetConveyer);
   _theChef->setOrigin(chefOrigin);
   
    _cloudTipsPos = Vec2(140, yOffsetConveyer + 100);
    
    _convY = yOffsetConveyer - 102;
    _convLegth = aVisibleSize.width;
    
    _conv = Conveyor::create(_bandVelosity, _convLegth);
    _conv->setPosition(Vec2(0, _convY));
    _gameLayer->addChild(_conv, kConveyurZO);
    
    _thePot = Pot::create(_gameLayer,kPotFrontZO,kPotBackZO);
   Size sz = _thePot->getFrontRect().size;
   Point potOrigin = Point(0,0);//Point(aVisibleSize.width/2.0f - sz.width/2.0f, 0.0f);
   _thePot->setOriginPos(potOrigin);
    
    _scoreLayer = ScoreLayer::create(0); 
    _scoreLayer->setPosition(Vec2(500, aVisibleSize.height + anOrigin.y - 100));
    _gameLayer->addChild(_scoreLayer, kCloudZO);

    _multiplier = Multiplier::create();
    _multiplier->setPosition(Vec2(450, aVisibleSize.height + anOrigin.y - 60));
    _gameLayer->addChild(_multiplier, kCloudZO);
    
    _gameCycleInd = GameCycleIndicator::createWithGameTime(_levelInfo->getRoundTime());
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

void startGame()
{

}

void GameController::restartGame() {
    _isControllerWaitingStop = false;
    this->setUpInit(false);
    _gameLayer->resume();
    _cloudTips->toggleTip();
    _conv->resumeConv();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(SOUND_BG, true);
}

void GameController::stopGame()
{
    _gameLayer->pause(); //unscheduleUpdate();
    Vector<Node*> children = _gameLayer->getChildren();
    for (int i= 0; i < children.size(); i++) {
        Node* node = children.at(i);
        if (node != nullptr) {
            if (dynamic_cast<Conveyor*>(node)) {
                ((Conveyor *) node)->pauseConv();
            } else {
                node->pause();
            }
        }
    }
    _cloudTips->setOpacity(127);
    //Director::getInstance()->pause();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameController::runItemConveyorAction(Item* anItem)
{
    float actionOffsetX = _itemIdlePos.x + anItem->getContentSize().width + 1;
    Vec2 targetPoint = Vec2(_itemIdlePos.x -  actionOffsetX, _itemIdlePos.y);
    float actionDuration = actionOffsetX/_bandVelosity;
    FiniteTimeAction* itemAction = anItem->getConveyourAction(actionDuration, targetPoint);
    float scaleFactor = this->getScaleFactor(_itemIdlePos, 0);
    anItem->setScale(scaleFactor);
    anItem->stopAllActions();
    anItem->runAction(itemAction);

}
void GameController::putItemOnConveyour(float dt)
{
    _elasedTest += dt;

    Item* item = _itemsPool->getItemFromPool(&_items, dt, _gameCycleInd->getGameTime(), kItemZO1, _bandVelosity);
    if(item){

        if(!item->getParent())
            _gameLayer->addChild(item,kItemZO1);
        
        Vec2 pos = item->getPosition();
        item->setPosition(_itemIdlePos);
        item->setLocalZOrder(kItemZO1);
        this->runItemConveyorAction(item);
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

void GameController::tossItem(Item* anItem, Vec2 anImpulse)
{
    //Point impulse
    ControlPointDef* collisionEndPointDef = nullptr;
    if (_cntPoints->size() > 0) {
        int randomPointIdx = getRandomNumber(0,(_cntPoints->size()-1));
        collisionEndPointDef = _cntPoints->at(randomPointIdx);
    }
    float totalActionDuration = 1.5f;
    this->runTossActionWithScale(anItem, collisionEndPointDef, totalActionDuration, anImpulse);
    anItem->playBounceSound();
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
       
       anItem->playHitPotSound();
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
          anItem->playCrashSound();
   }else
      if (currentCollisionType == kControlPointTypePotCenter){
         anItem->setLocalZOrder(kItemZO3);
          anItem->playHitPotSound();
          
          this->checkGameProgress(anItem);
      }
}

void GameController::resetActiveBonus()
{
    int activeBonus = _bonusMenu->getActiveBonus();
    switch (activeBonus) {
        case kBonusType1: // set chef blind
            _theChef->resetVision();
            break;
        case kBonusType2:
             _bandVelosity = _levelInfo->getSpeed();
            _conv->changeCyclingSpeed(_bandVelosity);
            break;
        case kBonusType3:
            break;
            
        default:
            break;
    }
    
    _bonusTimer = 0.0f;
    _bonusMenu->resetActiveBonus();

}

void GameController::useActiveBonus()
{
    int activeBonus = _bonusMenu->getActiveBonus();
    switch (activeBonus) {
        case kBonusType1: // set chef blind
            _theChef->setVision(_levelInfo->getRequiredItems());
            _bonusTimer = 20.0f;
            break;
        case kBonusType2:
            _bandVelosity = _bandVelosity/1.5f;
            _conv->changeCyclingSpeed(_bandVelosity);
            _bonusTimer = 20.0f;
            break;
        case kBonusType3:
            _bonusTimer =  _gameCycleInd->getGameTime() + _levelInfo->getRoundTime()/2.0f;
            _gameCycleInd->setGameTime(_bonusTimer);
            break;
            
        default:
            break;
    }
    
}

void GameController::processBonusState(float dt)
{

    if(_bonusTimer > 0.0f){
        _bonusTimer -= dt;
        if(_bonusTimer <= 0.0f)
            this->resetActiveBonus();
    }
    else{
        this->useActiveBonus();
    }
    
}

void GameController::update(float dt)
{
 
    _currGameTime += dt;
   Item* item = nullptr;
   Vec2 itemPos;
   Size itemSize;
    
    
    this->processBonusState(dt);
   _idxRotated = (_idxRotated + 1) < _items.size() ? (_idxRotated + 1) : 0;
    _gameCycleInd->nextStep(dt);
    
    if (_gameCycleInd->getGameTime() - _currGameTime < 8 && _gameCycleInd->getGameTime() - _currGameTime > 7) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_TIMER_BEFORE);
    } else
    
    if (_gameCycleInd->getGameTime() - _currGameTime < 4 && _gameCycleInd->getGameTime() - _currGameTime > 3) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_TIMER_END);
    }
    
    
    if (_gameCycleInd->isComplete()) {
        this->stopGame();
        
        if (this->_mainCource->checkAllRequiredExist(_caughtItemsIds)) {
            _isControllerWaitingStop = true;
        } else {                         //TODO: remove
            GameOverPopup* goPopup = GameOverPopup::create();
            _gameLayer->addChild(goPopup, 1001);
        }
        return;
    }

   
    if (_isControllerWaitingStop) {
        if(_theChef->isChefIdle()){
            this->stopGame();
            this->_nRound++;
            this->updatePerformanceMetrics();
            this->restartGame();
            _isControllerWaitingStop = false;
        }
    }
    else
        this->putItemOnConveyour(dt);
    
    for(Node* nitem : _items){
      
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
         
         Item* tossed = _theChef->looksForItem(item, this->_bandVelosity);
         if (tossed) {
            this->tossItem(tossed, _theChef->getBounceImpulse());
         }
            
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
             item->setLocalZOrder(kItemZO1);

         }
      
   }
    
}

ControlPointDef* GameController::findControlPointDefByAngle(Item* anItem, float angle, float xImpulse) {
   // angle = abs(angle);
    
    Point currentTargetPoint = anItem->_currentTargetPoint;
    
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
        if (_bonusMenu->checkItemToUpdateBonus(anItem)) {
            return; // if item is bonus, just increment collected bonuses;
        }
        //_caughtItemsIds.push_back(0);
        //_caughtItemsIds.push_back(3);
        //_caughtItemsIds.push_back(11);
        
        if (_mainCource->isRequiredItem(anItem->_itemId)) {
            _caughtItemsIds.push_back(anItem->_itemId);
            
            _scoreLayer->updateScore(10);
            int multiCount = _multiplier->update(anItem->_itemId);
            if (multiCount > 4) {
                _scoreLayer->updateScore(50);
                _multiplier->reset();
            }
            
            if (_mainCource->checkAllRequiredExist(_caughtItemsIds)) {
                _isControllerWaitingStop = true;
            }
            
        } else {
            //_scoreLayer->updateScore(0);
            _multiplier->reset();
        }
    }

}

float GameController::getActualRoundTime()
{
    return _gameCycleInd->getGameTime();
}

void GameController::updatePerformanceMetrics()
{
    
    float factor = (float)_nRound * 0.1f;
    
    //if(!_nRound%2)
        _bandVelosity = _maxBandVelosity * factor + 40;
    
    //_repeatIngridients = _maxRepeatIngridients - ;
    
    //_repeatBonus1;
    
    //_repeatBonus2;
    
    //_repeatBonus3;
    
    //if (!_nRound%3) {
        _garbagePct = _maxGarbagePct * factor;
    //}
    

    
/*
    _maxBandVelosity = 100;
    
    _maxRepeatIngridients = 3;
    
    _maxRepeatBonus1 = 3;
    
    _maxRepeatBonus2 = 3;
    
    _maxRepeatBonus3 = 3;
    
    _maxGarbagePct = 0.7;
*/
}



