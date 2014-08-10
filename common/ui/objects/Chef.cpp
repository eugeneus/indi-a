
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
   
   Rect handRect = aHand->getRect();
   float grabDistance = handRect.origin.x + handRect.size.width;
   float itemPosX = anItem->getPosition().x;
   
   return ( (itemPosX > handRect.origin.x) && (itemPosX < grabDistance));
}

Item* Chef::looksForItem(Item* anItem, float aConveyourVelocity)
{
   Hand* activeHand = _leftHand;
   if (_leftHand->isHandBusy()) { //  || _leftHand->isWaiting()
      activeHand = _rightHand;
   }
   
   if (this->isHandCanGrab(activeHand, anItem)) {
      activeHand->catchItem(anItem);
      activeHand->runAction(activeHand->getRiseHandAnimateAction(aConveyourVelocity));
   }
   
   if (activeHand->isHandBusy() ) { //&& !activeHand->randomWaitForToss()
      //activeHand->runTossAmiatedAction();
      Item* tossedItem = activeHand->dropItem();
      return tossedItem;
   }
   
   return nullptr;
}

bool Chef::tryToCatchItem(Item* anItem, float aConveyorVelocity)
{
   bool isItemCatch = false;
   _conveyorVelocity = aConveyorVelocity;

   Point itemPos = anItem->getPosition();
   bool isLeftHandSeep = false;
   if(_sleepCounter > 2){
      isLeftHandSeep = true;
      _sleepCounter = 0;
   }
   else
      _sleepCounter++;
   
   Sprite* activeHand = _leftHand;
   Rect activeHandRect = Rect(_leftHandRect);
   _activeBouncePoint = _leftHandRect.origin;
   
   if (isLeftHandSeep) {
      activeHand = _rightHand;
      activeHandRect = Rect(_rightHandRect);
      _activeBouncePoint = _rightHandRect.origin;
   }
   
   if((itemPos.x - _szWatchSector.width) <= (activeHandRect.origin.x + activeHandRect.size.width) &&
      itemPos.x - _szWatchSector.width > activeHandRect.origin.x &&
      itemPos.y >= activeHandRect.origin.y - _szWatchSector.height &&
      itemPos.y <= activeHandRect.origin.y
      ){
      //calulate parametes and start hands "grab" animation
      if (activeHand->getNumberOfRunningActions() == 0) {
         
         
         float catchPosX = itemPos.x + _szWatchSector.width * (((float)(0.0f + arc4random() % 11))/10.0f);
         catchPosX = catchPosX < itemPos.x ? catchPosX : itemPos.x - 1;
         
         float actualDuration = (itemPos.x - catchPosX)/_conveyorVelocity;

         ccBezierConfig bezier;
         Point cp1 = activeHandRect.origin;
         cp1.y = itemPos.y + 50.0f;
         cp1.x = itemPos.x + (itemPos.x - catchPosX)/2.0f;
         Point endPoint = Point(catchPosX,itemPos.y);
         bezier.controlPoint_1 = cp1;
         bezier.controlPoint_2 = endPoint;
         bezier.endPosition = endPoint;
         
         BezierTo* catchBz = BezierTo::create(actualDuration, bezier);
         RotateTo* catchRt = RotateTo::create(actualDuration, 90.0f);
         Spawn* catchAction = Spawn::create(catchBz,catchRt,NULL);
         
         MoveTo* tossMv = MoveTo::create(0.1, activeHandRect.origin);
         RotateTo* tossRt = RotateTo::create(0.1, -90.0f);
         Spawn* tossAction = Spawn::create(tossMv,tossRt,NULL);
         
         //≥activeHand->runAction(Sequence::create(catchAction,tossAction, NULL));
         
         activeHand->runAction(this->getHandGrabAnimation());
         
         //this->runGrabAnimation(activeHand, itemPos, activeHandRect);
         this->updateBounceImpulse();
         isItemCatch = true;
      }
   }
   
   return isItemCatch;
}

void Chef::chefWathItem(Item* anItem)
{
   Point itemPos = anItem->getPosition();
   
   bool isLeftHandSeep = false;
   if(_sleepCounter > 2){
      isLeftHandSeep = true;
       _sleepCounter = 0;
   }
   else
      _sleepCounter++;

   Sprite* activeHand = _leftHand;
   Rect activeHandRect = Rect(_leftHandRect);
   _activeBouncePoint = _leftHandRect.origin;
   
   if (isLeftHandSeep) {
      activeHand = _rightHand;
      activeHandRect = Rect(_rightHandRect);
      _activeBouncePoint = _rightHandRect.origin;
   }

 
   if((itemPos.x - _szWatchSector.width) <= (activeHandRect.origin.x + activeHandRect.size.width) &&
      itemPos.x - _szWatchSector.width > activeHandRect.origin.x &&
      itemPos.y >= activeHandRect.origin.y - _szWatchSector.height &&
      itemPos.y <= activeHandRect.origin.y
      ){
      if (activeHand->getNumberOfRunningActions() == 0) {
         
         //this->runGrabAnimation(activeHand, itemPos, activeHandRect);

         this->updateBounceImpulse();
      }
   }
   
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

void Chef::startHandBounceAnimation()
{

}

Animate* Chef::getHandGrabAnimation()
{
   Vector<SpriteFrame*> animFrames(4);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = 1; i < 5; i++)
   {
      sprintf(imageFileName, "hand_left_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }
   
   Animation* animation = Animation::createWithSpriteFrames(animFrames, 1.0f);
   
   return Animate::create(animation);
   
}

void Chef::runGrabAnimation(Sprite* activeHand, Point itemPos, Rect activeHandRect)
{
   float actionGrabDistanceActual = 0.0f;
   float actionGrabDuration = 0.0f;
   cocos2d::MoveTo* grabActionUp = nullptr;
   cocos2d::MoveTo* grabActionDown = nullptr;

   actionGrabDistanceActual = itemPos.x - activeHandRect.origin.x;
   actionGrabDuration = actionGrabDistanceActual/_conveyorVelocity; //
   grabActionUp = MoveTo::create(actionGrabDuration * 0.15,
                                 Vec2(activeHandRect.origin.x,activeHandRect.origin.y + actionGrabDistanceActual/2.0));
   
   
   grabActionUp->setTag(1);
   grabActionDown = MoveTo::create(actionGrabDuration * 0.15, Vec2(activeHandRect.origin.x,activeHandRect.origin.y));
   grabActionDown->setTag(2);
   
   cocos2d::MoveTo* grabActionDown1 = MoveTo::create(actionGrabDuration * 0.15, Vec2(activeHandRect.origin.x,activeHandRect.origin.y - 50.0f));
   grabActionDown1->setTag(3);
   
   Vector<SpriteFrame*> animFrames(4);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = 1; i < 5; i++)
   {
      sprintf(imageFileName, "hand_left_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }

   Animation* animation = Animation::createWithSpriteFrames(animFrames, actionGrabDuration * 0.15);
   
   
   cocos2d::MoveTo* grabActionDown2 = MoveTo::create(actionGrabDuration * 0.15,
                                                     Vec2(activeHandRect.origin.x,
                                                          activeHandRect.origin.y +actionGrabDistanceActual));
   grabActionDown2->setTag(5);
   
   cocos2d::MoveTo* grabActionDown3 = MoveTo::create(actionGrabDuration * 0.15,
                                                     Vec2(activeHandRect.origin.x,
                                                          activeHandRect.origin.y));
   /*
   activeHand->runAction(Sequence::create(grabActionUp,grabActionDown,
                                          Spawn::create(grabActionDown1,
                                                        Animate::create(animation),NULL),
                                          grabActionDown2,grabActionDown3,NULL));
   */
   activeHand->runAction(Animate::create(animation));

}
/*
void Chef::runGrabAnimation(Sprite* activeHand, Point itemPos, Rect activeHandRect)
{
   float actionGrabDistanceActual = 0.0f;
   float actionGrabDuration = 0.0f;
   cocos2d::MoveTo* grabActionUp = nullptr;
   cocos2d::MoveTo* grabActionDown = nullptr;
   
   actionGrabDistanceActual = itemPos.x - activeHandRect.origin.x;
   actionGrabDuration = actionGrabDistanceActual/_conveyorVelocity; //
   grabActionUp = MoveTo::create(actionGrabDuration * 0.15,
                                 Vec2(activeHandRect.origin.x,activeHandRect.origin.y + actionGrabDistanceActual/2.0));
   
   
   grabActionUp->setTag(1);
   grabActionDown = MoveTo::create(actionGrabDuration * 0.15, Vec2(activeHandRect.origin.x,activeHandRect.origin.y));
   grabActionDown->setTag(2);
   
   cocos2d::MoveTo* grabActionDown1 = MoveTo::create(actionGrabDuration * 0.15, Vec2(activeHandRect.origin.x,activeHandRect.origin.y - 50.0f));
   grabActionDown1->setTag(3);
   
   Vector<SpriteFrame*> animFrames(3);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = 1; i < 4; i++)
   {
      sprintf(imageFileName, "hand_left_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }
   
   Animation* animation = Animation::createWithSpriteFrames(animFrames, actionGrabDuration * 0.15);
   
   
   cocos2d::MoveTo* grabActionDown2 = MoveTo::create(actionGrabDuration * 0.15,
                                                     Vec2(activeHandRect.origin.x,
                                                          activeHandRect.origin.y +actionGrabDistanceActual));
   grabActionDown2->setTag(5);
   
   cocos2d::MoveTo* grabActionDown3 = MoveTo::create(actionGrabDuration * 0.15,
                                                     Vec2(activeHandRect.origin.x,
                                                          activeHandRect.origin.y));
   
   activeHand->runAction(Sequence::create(grabActionUp,grabActionDown,
                                          Spawn::create(grabActionDown1,
                                                        Animate::create(animation),NULL),
                                          grabActionDown2,grabActionDown3,NULL));
   
}
*/

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




