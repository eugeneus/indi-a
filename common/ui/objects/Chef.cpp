
#include "Chef.h"
#include "Item.h"
#include "Hand.h"

USING_NS_CC;

Chef::Chef()
{
   //_rightHandRect = Rect(0.0f, 0.0f, 0.0f, 0.0f);
   _bounceImpulse = Vec2(1.0f, 1.0f);
}
 
Chef::~Chef(){}


Chef* Chef::create(cocos2d::Layer* aLayer, int aZOrder)
{
    Chef *pRet = new Chef();
    if (pRet && pRet->init(aLayer,aZOrder))
    {
        //pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Chef::init(cocos2d::Layer* aLayer, int aZOrder) {
   
   _szWatchSector = Size(5.0f,145.0f);
   _sleepCounter = 0;
   
   Size visibleSize = Director::getInstance()->getVisibleSize();
   this->_layer = aLayer;
   
   _chef = Sprite::createWithSpriteFrameName("chef_1.png");
   _chef->setAnchorPoint(Point(0,0));
   aLayer->addChild(_chef,4);
    
    _head = Sprite::createWithSpriteFrameName("head_idle_1.png");
    _head->setAnchorPoint(Point(0,0));
    
    aLayer->addChild(_head,4);
   
   // just temporary scale
   float scaleFactor = 0.65f;
   _chef->setScale(scaleFactor);
    //_head->setScale(scaleFactor);
   Size chefSize = _chef->getContentSize();
   Point chefOrigin = Point((visibleSize.width - (chefSize.width*scaleFactor))/2.0f, 0.0f);
   _chef->setPosition(chefOrigin);
   _chefRect = Rect(chefOrigin.x,chefOrigin.y,chefSize.width*scaleFactor,chefSize.height*scaleFactor);
   _head->setPosition(Vec2(_chefRect.origin.x + _chefRect.size.width/2.0,_chefRect.origin.y + _chefRect.size.height));
   
   // positions will be adjusted by setOrigin
   _rightHand = Hand::create("hand_left_1.png");
   aLayer->addChild(_rightHand,aZOrder);
   _rightHand->setFlippedX(true);
   
   _leftHand = Hand::create("hand_left_1.png");
   aLayer->addChild(_leftHand,aZOrder);
   
   return true;
}

void Chef::setScale(float aScaleFactor) {
    
}


cocos2d::Size Chef::getSize()
{
   return _chefRect.size;
}

void Chef::setOrigin(cocos2d::Point anOrigin)
{

   _chefRect.origin.x = anOrigin.x;
   _chefRect.origin.y = anOrigin.y;
    float xOffset = (_leftHand->getContentSize().width*0.7)*0.2;
    _rightHandRect.origin.x = anOrigin.x + xOffset;
   _rightHandRect.origin.y = anOrigin.y + 20.0f;

    float xPos = anOrigin.x + _chefRect.size.width - xOffset;
   _leftHandRect.origin.x = xPos;
   _leftHandRect.origin.y = anOrigin.y + 20.0f;

   _chef->setPosition(_chefRect.origin);
    Size headSize = _head->getContentSize();
   _head->setPosition(Vec2(_chefRect.origin.x + _chefRect.size.width/2.0 - headSize.width / 2.0f,
                           _chefRect.origin.y + _chefRect.size.height - 30.0f));

   _leftHand->setInitialPosition(_leftHandRect.origin);
   _rightHand->setInitialPosition(_rightHandRect.origin);

}

void Chef::setWatchSector(cocos2d::Size aSectorSize)
{
   _szWatchSector = aSectorSize;
}

bool Chef::isHandCanGrab(Hand* aHand, Item* anItem)
{
   return anItem->getLocalZOrder() == 20 && aHand->isCanGrabItem(anItem);
}

bool Chef::isHandShouldGrabItem(Hand* aHand, Item *anItem)
{
    return this->isHandCanGrab(aHand, anItem) && ((this->hasVision() && this->isRequiredItem(anItem)) || !this->hasVision());
}

void Chef::setVision(std::vector<int> aRequiredItems)
{
    _requiredItemIDs = aRequiredItems;
}

void Chef::resetVision()
{
    _requiredItemIDs.clear();
}


bool Chef::hasVision()
{
    return _requiredItemIDs.size() > 0;
}

bool Chef::isRequiredItem(Item* anItem)
{
    int iReqItem = 0;
    bool isRequiredItem = false;
    while (!isRequiredItem && iReqItem < _requiredItemIDs.size()) {
        isRequiredItem = (anItem->getItemId() == _requiredItemIDs.at(iReqItem));
        iReqItem++;
    }
    
    return isRequiredItem;
}

bool Chef::isItemAccesible(Item* anItem)
{
   float minX = _chefRect.origin.x;
   float maxX = _chefRect.origin.x + _chefRect.size.width + _leftHandRect.size.width;
   float itemPosX = anItem->getPosition().x;
   
   return (itemPosX >= minX && itemPosX <= maxX) && anItem->getLocalZOrder() == 20;
}

/*
void Chef::resetHands()
{
    _leftHand->getNumberOfRunningActions() == 0
    //this->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("egg_1.png"));
}
*/
// chef entry point
Item* Chef::looksForItem(Item* anItem, float aConveyourVelocity)
{
   // initially ignore long distance items
    
   
   if (!this->isItemAccesible(anItem)) {
      return nullptr;
   }
    
   Item* tossingItem = nullptr;
   // left hand processing
   if (_leftHand->isCaughtItem(anItem)) {

       tossingItem = _leftHand->tossItem();
      if (tossingItem) {
         return tossingItem;
      }
      _leftHand->upItem();
   }
   else if(_leftHand->isHandBusy() && !_leftHand->isCaughtItem(anItem)){
      
      _leftHand->setIgnoredItem(anItem);
   
   }
   else if(this->isHandShouldGrabItem(_leftHand, anItem)){
   
      _leftHand->catchItem(anItem);
      _leftHand->runGrabAnimatedAction(aConveyourVelocity);
   }
   
   // rigth Hand processing
   
   if (_rightHand->isCaughtItem(anItem)) {
      
      tossingItem = _rightHand->tossItem();
      if (tossingItem) {
         return tossingItem;
      }
      
      _rightHand->upItem();
      
   }
   else if(_rightHand->isHandBusy() && !_rightHand->isCaughtItem(anItem)){
       _rightHand->setIgnoredItem(anItem);
   }
   else if(this->isHandShouldGrabItem(_rightHand, anItem)) {
      
      _rightHand->catchItem(anItem);
      _rightHand->runGrabAnimatedAction(aConveyourVelocity);
   }
   
   return nullptr;
}

void  Chef::startChefBodyAnimation()
{
   Vector<SpriteFrame*> animFrames(15);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = 1; i < 11; i++)
   {
      sprintf(imageFileName, "chef_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }
   
   Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3);

   _chef->runAction(RepeatForever::create(Animate::create(animation)));
    
    this->startChefHeadIdleAnimation();
   
}

void  Chef::startChefHeadIdleAnimation()
{
    Vector<SpriteFrame*> animFrames(15);
    char imageFileName[100] = {0};
    auto cache = SpriteFrameCache::getInstance();
    for(int i = 2; i < 23; i++)
    {
        sprintf(imageFileName, "head_idle_%d.png", i);
        SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
        animFrames.pushBack(frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3);
    
    _head->runAction(RepeatForever::create(Animate::create(animation)));
    
}

void Chef::updateBounceImpulse()
{
   //TODO: do it random
   _bounceImpulse.x -= 0.25f;
   _bounceImpulse.x  = _bounceImpulse.x < -1.0 ? _bounceImpulse.x : 1.0f;
   
   _bounceImpulse.y -= 0.3f;
   _bounceImpulse.y  = _bounceImpulse.y < 0.2 ? _bounceImpulse.x : 1.0f;
   
}

Point Chef::getActiveBouncePoint()
{
   return _activeBouncePoint;
}


Vec2 Chef::getBounceImpulse()
{
   return _bounceImpulse;
}

void Chef::setZOrder(int aZOrder)
{
   
}

void Chef::setConveyorVelocity(float aConveyorVelocity)
{
   _conveyorVelocity = aConveyorVelocity;
}

void Chef::restartChef() {
    _leftHand->restart();
    _rightHand->restart();
    _chef->stopAllActions();
    _head->stopAllActions();
    this->startChefBodyAnimation();
}

bool Chef::isChefIdle()
{
    return _leftHand->isHandIdle() && _rightHand->isHandIdle();
}




