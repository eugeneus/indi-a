
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
   pRet->_tossPoint = Point(pRet->_handRect.origin.x + pRet->_handRect.size.width/2.0f,
                            pRet->_handRect.origin.y + pRet->_handRect.size.height/2.0f);
   
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
   this->_tossPoint = Point(_handRect.origin.x + _handRect.size.width/2.0f,
                            _handRect.origin.y + _handRect.size.height/2.0f);

   
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

Item* Hand::tossItem()
{
   Item* tossingItem = nullptr;
   if (!_catchItem) {
      return tossingItem;
   }
   
   if (_catchItem->getPosition().x >= _tossPoint.x - 1.0f &&
       _catchItem->getPosition().x <= _tossPoint.x + 1.0f) {
      
      this->runTossAmiatedAction();
      return this->dropItem();
      
   }
   
   return nullptr;
}

bool Hand::isHandBusy()
{
   Point currHandPos = this->getPosition();
   Point handPos = Point((_handRect.origin.x + _handRect.size.width / 2.0f), (_handRect.origin.y + _handRect.size.height / 2.0f));
   bool isHandBusy = ((handPos.x != currHandPos.x) || (handPos.y != currHandPos.y)) && (_catchItem);
   return isHandBusy;
}

Rect Hand::getRect()
{
   return _handRect;
}

bool Hand::waitIgnoredItem()
{
   return false;
}

void Hand::runGrabAnimatedAction(float aConveyorVelocity)
{
   Point pos = _catchItem->getPosition();
   float duration = (pos.x - this->_tossPoint.x)/aConveyorVelocity;
   
   Animation* animation = this->getAnimation(1,2, (duration/2.0));
   pos.x = _tossPoint.x;
   pos.y = pos.y + _catchItem->getContentSize().height/2.0f;
   Point pos1 = Point(_handRect.origin.x + _handRect.size.width/2.0f,_handRect.origin.y + _handRect.size.height/2.0f);
   MoveTo* move1 = MoveTo::create(duration/2.0f,  pos1); // todo move point
   MoveTo* move2 = MoveTo::create(duration/2.0f, pos); // todo move point
   
   this->runAction(Spawn::create(Sequence::create(move1,move2, NULL),Animate::create(animation),NULL));

}
void Hand::runTossAmiatedAction()
{
   /*
   auto cache = SpriteFrameCache::getInstance();
   Vector<SpriteFrame*> animFrames(2);
   animFrames.pushBack(cache->getSpriteFrameByName("hand_left_3.png"));
   animFrames.pushBack(cache->getSpriteFrameByName("hand_left_4.png"));
   */
   Animation* tossAnimation = this->getAnimation(3,4, 0.5);
   
   Animation* retAnimation = this->getAnimation(1,1, 0.1);
   MoveTo* moveRet = MoveTo::create(1.2, _handRect.origin);
   
   Sequence* seq = Sequence::create(Animate::create(tossAnimation), Animate::create(retAnimation), NULL);
   
   this->runAction(Spawn::create(moveRet,seq, NULL));
   
}

