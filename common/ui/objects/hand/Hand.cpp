
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
   
   if (!pRet->initWithSpriteFrameName(aSpriteFrameName)){
      delete pRet;
      pRet = nullptr;
      return pRet;
   }
   
   Size imgSize = pRet->getContentSize();
   pRet->_handRect = Rect(0.0f, 0.0f, imgSize.width, imgSize.height);
   pRet->setAnchorPoint(Point(0.5f,0.5f));
   pRet->setScale(0.7);
   pRet->_grabPoint = pRet->getPosition();
   pRet->_tossPoint = Point(pRet->_grabPoint.x, pRet->_grabPoint.y + pRet->_handRect.size.height / 2.0f);
   
   //pRet->testDraw();

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

void Hand::setInitialPosition(cocos2d::Point aPosition)
{
   this->_handRect.origin.x = aPosition.x;
   this->_handRect.origin.y = aPosition.y;
   this->_grabPoint = aPosition;
   this->_tossPoint = Point(_grabPoint.x, _grabPoint.y + _handRect.size.width / 2.0f);
   
   Sprite::setPosition(aPosition);
}

void Hand::catchItem(Item* anItem)
{
   if (this->_catchItem) {
      return;
   }
   
   this->_catchItem = anItem;
   this->_grabPoint.y = _catchItem->getPosition().y;
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

void Hand::upItem()
{
   if (!_catchItem) {
      return;
   }
   Point currPos = _catchItem->getPosition();
   
   if (currPos.x >= _grabPoint.x - 1.0f &&
       currPos.x <= _grabPoint.x + 1.0f &&
       currPos.y == _grabPoint.y) {
      currPos.y += 0.1f;
      _catchItem->setPosition(currPos);
      this->runHandUpAnimatedAction();
   }

}

Item* Hand::tossItem()
{
   //Item* tossingItem = nullptr;
   if (!_catchItem) {
      return nullptr;
   }
   Point currPos = _catchItem->getPosition();
   if (currPos.x >= _tossPoint.x - 1.0f &&
       currPos.x <= _tossPoint.x + 1.0f &&
       currPos.y == _tossPoint.y) {
      currPos.y += 0.1f;
      _catchItem->setPosition(currPos);
      this->runTossAmiatedAction();
      
      return this->dropItem();
   }
   
   return nullptr;
}

bool Hand::isHandBusy()
{
   //Point currHandPos = this->getPosition();
   //Point handPos = Point((_handRect.origin.x + _handRect.size.width / 2.0f), (_handRect.origin.y + _handRect.size.height / 2.0f));
   //((handPos.x != currHandPos.x) || (handPos.y != currHandPos.y)) &&
   bool isHandBusy = ((_catchItem) &&
   (this->getNumberOfRunningActions() > 0));
   return isHandBusy;
}

Rect Hand::getRect1()
{
   return _handRect;
}

/*
bool Hand::waitIgnoredItem()
{
   return false;
}
*/ 

void Hand::runGrabAnimatedAction(float aConveyorVelocity)
{
   Point pos = _catchItem->getPosition();
   float duration = (pos.x - this->_grabPoint.x)/aConveyorVelocity;
   
   Animation* animation = this->getAnimation(1,2, (duration/2.0));
   pos = Point(_handRect.origin.x + _handRect.size.width/2.0f,_handRect.origin.y + _handRect.size.height/2.0f);
   MoveTo* move1 = MoveTo::create(duration/2.0f,  pos);
   Point pos2 = Point(_grabPoint.x,_grabPoint.y + _catchItem->getScaledContentSize().height/2.0f);
   MoveTo* move2 = MoveTo::create(duration/2.0f, pos2);
   
   this->runAction(Spawn::create(Sequence::create(move1,move2, NULL),Animate::create(animation),NULL));

}

void Hand::runHandUpAnimatedAction()
{
   float duration = 0.5f;
   Point itemPos = _catchItem->getPosition();
   float actionDistance = abs(_tossPoint.y - itemPos.y);
   
   Point currPos = this->getPosition();
   Point upPoint = Point(currPos.x, currPos.y + actionDistance); //currPos.y + (_tossPoint.y - currPos.y)
   
   MoveTo* moveUp = MoveTo::create(duration, upPoint);
   Animation* animation = this->getAnimation(3,3, duration);
   Spawn* moveUpSpawn = Spawn::create(moveUp, Animate::create(animation), NULL);
   this->runAction(moveUpSpawn);
   
   _catchItem->runCatchAction(duration,_tossPoint);
}

void Hand::runTossAmiatedAction()
{
   Animation* tossAnimation = this->getAnimation(4,4, 0.5);
   
   Animation* retAnimation = this->getAnimation(1,1, 0.1);
   MoveTo* moveRet = MoveTo::create(1.2, _handRect.origin);
   
   Sequence* seq = Sequence::create(Animate::create(tossAnimation), Animate::create(retAnimation), NULL);
   
   this->runAction(Spawn::create(moveRet,seq, NULL));
   
}

void Hand::setIgnoredItem(Item* anItem)
{
   if(!this->_ignoredItem){
      
      _ignoredItem = anItem;
      
   }
   else{ // reset item if it did go away
      
      Point currPos = this->_ignoredItem->getPosition();
      if(currPos.x < this->_handRect.origin.x ||
         currPos.x > (this->_handRect.origin.x + _handRect.size.width + 1.0f) ||
         anItem->getLocalZOrder() != 20
         )
         this->_ignoredItem = nullptr;
   }
   
   
}

bool Hand::isIgnoredItem(Item* anItem)
{
   return _ignoredItem == anItem;
}

bool Hand::isCaughtItem(Item* anItem)
{
   return _catchItem == anItem;
}

bool Hand::isCanGrabItem(Item* anItem)
{
   if(this->isIgnoredItem(anItem))
      return false;
   
   float grabDistance = _handRect.origin.x + (_handRect.size.width / 2.0f);
   float itemPosX = anItem->getPosition().x;

   return ( (itemPosX > _handRect.origin.x) && (itemPosX < grabDistance));
}


void Hand::testDraw()
{
   // draw anchor point
    DrawNode *dotAnchorNode = DrawNode::create();
    dotAnchorNode->drawDot(this->getAnchorPointInPoints(), 10, Color4F(Color3B::WHITE));
    this->addChild(dotAnchorNode, 0);
   // draw position poing
   DrawNode *dotPositinNode = DrawNode::create();
   dotPositinNode->drawDot(this->getPosition(), 10, Color4F(Color3B::WHITE));
   this->addChild(dotPositinNode, 0);
   // draw content rect
 
   DrawNode *rectNode = DrawNode::create();
   Size imgSize = this->getContentSize();
   Point originPos = this->getPosition();
   Point point1 = originPos;
   point1.x += imgSize.width;
   Point point2 = point1;
   point2.y += imgSize.height;
   Point point3 = point2;
   point3.x = originPos.x;
   Point verts1 [] = {originPos,point1,point2,point3};
   
   rectNode->drawPolygon(verts1, 4, Color4F(1,1,1,0.2), 1.0, Color4F(Color3B::WHITE));
   this->addChild(rectNode, 0);
}

void Hand::restart() {
    _catchItem = nullptr;
    
    _ignoredItem = nullptr;
    this->stopAllActions();
    this->setPosition(_handRect.origin);
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hand_left_1.png"));
}

