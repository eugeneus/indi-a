
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
   
   _szWatchSector = Size(10.0f,140.0f);
   _sleepCounter = 0;
   
   Size visibleSize = Director::getInstance()->getVisibleSize();
   this->_layer = aLayer;
   
   _chef = Sprite::createWithSpriteFrameName("chef_1.png");
   _chef->setAnchorPoint(Point(0,0));
   aLayer->addChild(_chef,aZOrder - 10);
   
   // just temporary scale
   float scaleFactor = 0.5f;
   _chef->setScale(scaleFactor);
   Size chefSize = _chef->getContentSize();
   Point chefOrigin = Point((visibleSize.width - (chefSize.width*scaleFactor))/2.0f, 0.0f);
   _chef->setPosition(chefOrigin);
   _chefRect = Rect(chefOrigin.x,chefOrigin.y,chefSize.width*scaleFactor,chefSize.height*scaleFactor);
   
   // positions will be adjusted by setOrigin
   _rightHand = Hand::create("hand_left_1.png");
   aLayer->addChild(_rightHand,aZOrder);
   _rightHand->setFlippedX(true);
   
   _leftHand = Hand::create("hand_left_1.png");
   aLayer->addChild(_leftHand,aZOrder);
   
   return true;
}

void Chef::setScale(float aScaleFactor)
{

}


cocos2d::Size Chef::getSize()
{
   return _chefRect.size;
}

void Chef::setOrigin(cocos2d::Point anOrigin)
{

   _chefRect.origin.x = anOrigin.x;
   _chefRect.origin.y = anOrigin.y;
   float xOffset = (_leftHand->getContentSize().width*0.7)*0.5;
   _rightHandRect.origin.x = anOrigin.x + xOffset;
   _rightHandRect.origin.y = anOrigin.y;

   float xPos = anOrigin.x + _chefRect.size.width - xOffset;
   _leftHandRect.origin.x = xPos;
   _leftHandRect.origin.y = anOrigin.y;

   _chef->setPosition(_chefRect.origin);
   _leftHand->setPosition(_leftHandRect.origin);
   _rightHand->setPosition(_rightHandRect.origin);

}

void Chef::setWatchSector(cocos2d::Size aSectorSize)
{
   _szWatchSector = aSectorSize;
}

bool Chef::isHandCanGrab(Hand* aHand, Item* anItem)
{
   if(anItem->getLocalZOrder() > 20)
      return false;
   
   if(aHand->isIgnoredItem(anItem))
      return false;
   
   Rect handRect = aHand->getRect1();
   float grabDistance = handRect.origin.x + (handRect.size.width / 2.0f);
   float itemPosX = anItem->getPosition().x;
   
   return ( (itemPosX > handRect.origin.x) && (itemPosX < grabDistance));
}

bool Chef::isItemAccesible(Item* anItem)
{
   float minX = _rightHand->getRect1().origin.x;
   float maxX = _leftHand->getRect1().origin.x + _leftHand->getRect1().size.width;
   float itemPosX = anItem->getPosition().x;
   
   return (itemPosX >= minX && itemPosX <= maxX);
}

Item* Chef::looksForItem(Item* anItem, float aConveyourVelocity)
{
   // initially ignore long distance items TODO!!!
   if (!this->isItemAccesible(anItem)) {
      return nullptr;
   }
   
   // check if any hand ready to toss catched item
   Item* tossingItem = nullptr;
   tossingItem = _leftHand->tossItem();
   if (tossingItem) {
      return tossingItem;
   }
   
   tossingItem = _rightHand->tossItem();
   if (tossingItem) {
      return tossingItem;
   }
   
   // try to up catched item
   _leftHand->upItem();
   _rightHand->upItem();
   
   // check to forget ignored item
   _leftHand->forgetIgnoredItem();
   _rightHand->forgetIgnoredItem();
   
   // check if any hand can catch an item
   Hand* activeHand = _leftHand;

 if (_leftHand->isHandBusy()) { //  || _leftHand->isWaiting()
    _leftHand->setIgnoredItem(anItem);
      activeHand = _rightHand;
   }

   if (this->isHandCanGrab(activeHand, anItem)) {
      if (activeHand->isHandBusy()) {
         activeHand->setIgnoredItem(anItem);
      }
      else{
         activeHand->catchItem(anItem);
         activeHand->runGrabAnimatedAction(aConveyourVelocity);
      }
   }

   return nullptr;
}

void  Chef::startChefBodyAnimation()
{
   Vector<SpriteFrame*> animFrames(15);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = 1; i < 5; i++)
   {
      sprintf(imageFileName, "chef_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }
   
   Animation* animation = Animation::createWithSpriteFrames(animFrames, 2.5);

   _chef->runAction(RepeatForever::create(Animate::create(animation)));
   
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




