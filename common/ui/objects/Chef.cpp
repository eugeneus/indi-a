
#include "Chef.h"
#include "Item.h"

USING_NS_CC;

Chef::Chef()
{
   _rightHandRect = Rect(0.0f, 0.0f, 0.0f, 0.0f);
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
   
//"chef_1.png", "chef_%i.png", 4, 0.9
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
   
   float HscaleFactor = 0.7f;
   
   _rightHand = Sprite::createWithSpriteFrameName("hand_left_1.png");
   aLayer->addChild(_rightHand,aZOrder);
   _rightHand->setAnchorPoint(Point(0,0));
   _rightHand->setScale(HscaleFactor);
   _rightHand->setFlippedX(true);

   Size handSize = _rightHand->getContentSize();
   handSize.width = handSize.width*HscaleFactor;
   handSize.height = handSize.height*HscaleFactor;
   _rightHandRect = Rect(chefOrigin.x,chefOrigin.y,handSize.width,handSize.height);
   _rightHand->setPosition(_rightHandRect.origin);
   
   _leftHand = Sprite::createWithSpriteFrameName("hand_left_1.png");
   aLayer->addChild(_leftHand,aZOrder);
   _leftHand->setAnchorPoint(Point(0,0));
   _leftHand->setScale(HscaleFactor);
   
   float xPos = chefOrigin.x + _chefRect.size.width - ((handSize.width)/2.0f + 50.0f);
   _leftHandRect = Rect(_rightHandRect);
   _leftHandRect.origin.x = xPos;
   _leftHand->setPosition(_leftHandRect.origin);
   
   
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
   _rightHandRect.origin.x = anOrigin.x;
   _rightHandRect.origin.y = anOrigin.y;

   float xPos = anOrigin.x + _chefRect.size.width - ((_leftHandRect.size.width)/2.0f + 50.0f);
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


void Chef::chefWathItem(Item* anItem)
{
   Point itemPos = anItem->getPosition();
   //float actionGrabDistanceActual = 0.0f;
   //float actionGrabDuration = 0.0f;
   //cocos2d::MoveTo* grabActionUp = nullptr;
   //cocos2d::MoveTo* grabActionDown = nullptr;
   
   bool isLeftHandSeep = false;//(((int)0 + arc4random() % (2)) > 0);
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
         
         this->runGrabAnimation(activeHand, itemPos, activeHandRect);

         this->updateBounceImpulse();
      }

      // after that run hands "throw animation" simultaneously with item "throw" animation
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
   
/*
   auto cache = AnimationCache::getInstance();
   cache->addAnimationsWithFile("images.plist");
   auto animation = cache->getAnimation("chef");
   auto animate = Animate::create(animation);
   _chef->runAction(animate);
*/
   
}

void Chef::startHandBounceAnimation()
{

}

void Chef::runGrabAnimation(Sprite* activeHand, Point itemPos, Rect activeHandRect)
{
   float actionGrabDistanceActual = 0.0f;
   float actionGrabDuration = 0.0f;
   cocos2d::MoveTo* grabActionUp = nullptr;
   cocos2d::MoveTo* grabActionDown = nullptr;

   actionGrabDistanceActual = itemPos.x - activeHandRect.origin.x;
   float convVelocity = 50.0; TODO: // get actual conveyor velocity
   actionGrabDuration = actionGrabDistanceActual/convVelocity; //
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


void Chef::updateBounceImpulse()
{
   //TODO: do it random
   _bounceImpulse.x -= 0.2f;
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




