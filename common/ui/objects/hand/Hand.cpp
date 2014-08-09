
#include "Hand.h"
#include "Item.h"

USING_NS_CC;

Hand::Hand()
{
   _catchItem = nullptr;
   _ignoredItem = nullptr;
}

Hand::~Hand()
{
   _catchItem = nullptr;
}

Hand* Hand::create(const std::string &aSpriteFrameName)
{
   Hand *pRet = new Hand();
   //(Hand*)Sprite::createWithSpriteFrameName(aSpriteFrameName);
   
   if (!pRet->initWithSpriteFrameName(aSpriteFrameName)){
      delete pRet;
      pRet = nullptr;
      return pRet;
   }
   
   Size imgSize = pRet->getContentSize();
   pRet->_handRect = Rect(0.0f, 0.0f, imgSize.width* 0.7, imgSize.height*0.7);
//pRet->setScale(0.7f);
   pRet->setAnchorPoint(Point(0.5f,0.5f));
   pRet->setScale(0.7);
   //pRet->setFlippedX(true);
   
   

   return pRet;
}

Animation* Hand::getAnimation(int aFirtsImageIndex, int aLastImageIndex, float aDelay)
{
   
   Vector<SpriteFrame*> animFrames(4);
   char imageFileName[100] = {0};
   auto cache = SpriteFrameCache::getInstance();
   for(int i = aFirtsImageIndex; i < aLastImageIndex + 1; i++)
   {
      sprintf(imageFileName, "hand_left_%d.png", i);
      SpriteFrame* frame = cache->getSpriteFrameByName(imageFileName);
      animFrames.pushBack(frame);
   }
   
   return Animation::createWithSpriteFrames(animFrames, aDelay);
}

void Hand::mirrorImg() {
    this->setFlippedX(true);
}

float Hand::getRandomFloat(float from ,float to) {
   // seed the random
   srand (static_cast <unsigned> (time(0)));
   
   return from + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(to-from)));
   
}

bool Hand::randomWaitForToss()
{
   
   if(this->isHandBusy()){
      float maxPosX = _catchItem->getPosition().x;
      float minPosX = _handRect.origin.x;
      float waitDist = this->getRandomFloat(minPosX, maxPosX);
      
      if (maxPosX <= minPosX + waitDist) {
         return false;
      }
      
      return true;
   }
   
   return false;

}

void Hand::setPosition(cocos2d::Point aPosition)
{
   this->_handRect.origin.x = aPosition.x;
   this->_handRect.origin.y = aPosition.y;
   
   Sprite::setPosition(aPosition);
}


void Hand::catchItem(Item* anItem)
{
   this->_catchItem = anItem;
}

Item* Hand::dropItem()
{
   if(this->_catchItem ){ //&& this->_catchItem->getLocalZOrder() > 20
      Item* droppedItem = this->_catchItem;
      this->_catchItem = nullptr;
      return droppedItem;
   }
   
   return nullptr;
   
}

bool Hand::isHandBusy()
{
   return (bool)_catchItem;
}

Rect Hand::getRect()
{
   return _handRect;
}

bool Hand::waitIgnoredItem()
{
   return false;
}

FiniteTimeAction* Hand::getRiseHandAnimateAction()
{
   Animation* animation = this->getAnimation(1,2, 0.5);
   Point pos = _catchItem->getPosition();
   pos.y += pos.y + _catchItem->getContentSize().height;
   MoveTo* move = MoveTo::create(0.3, _handRect.origin); // todo move point
   return Spawn::create(move,Animate::create(animation),NULL);
}

FiniteTimeAction* Hand::runTossAmiatedAction()
{
   Animation* animationGrab = this->getAnimation(2,3, 0.5);
   Point pos = _catchItem->getPosition();
   //pos.y += pos.y + _catchItem->getContentSize().height/2.0f;
   MoveTo* moveGrab = MoveTo::create(0.3, _handRect.origin);
   Spawn* aniGrab = Spawn::create(moveGrab, Animate::create(animationGrab),NULL);
   
   Animation* animationToss = this->getAnimation(3,4, 0.3);
   pos = _catchItem->getPosition();
   pos.y += pos.y + _catchItem->getContentSize().height;
   MoveTo* moveToss = MoveTo::create(0.3, pos);
   Spawn* aniToss = Spawn::create(moveToss, Animate::create(animationToss),NULL);

   auto cache = SpriteFrameCache::getInstance();
   Vector<SpriteFrame*> animFrames(2);
   animFrames.pushBack(cache->getSpriteFrameByName("hand_left_4.png"));
   animFrames.pushBack(cache->getSpriteFrameByName("hand_left_1.png"));
   
   MoveTo* moveRet = MoveTo::create(0.5, _handRect.origin);
   Spawn* aniRet = Spawn::create(moveRet,Animate::create(Animation::createWithSpriteFrames(animFrames, 0.3)), NULL);

   this->runAction(Sequence::create(aniGrab,aniRet,NULL)); //
}

float getRandomFloat(float from ,float to) {
   // seed the random
   srand (static_cast <unsigned> (time(0)));
   
   return from + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(to-from)));
   
}


/*
 bool Hand::init() {
 
 
 handImg = Sprite::createWithSpriteFrameName("hand_left_1.png");
 this->setContentSize(handImg->getContentSize());
 
 this->addChild(handImg, 0);
 
 
 return true;
 }
 */

