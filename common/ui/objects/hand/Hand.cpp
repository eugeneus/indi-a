
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
   pRet->_handRect = Rect(0.0f, 0.0f, imgSize.width* 0.7, imgSize.height);
//pRet->setScale(0.7f);
   
   pRet->setAnchorPoint(Point(0.5f,0.5f));
   
/*
   pRet->_grabPoint = Point(pRet->_handRect.origin.x + pRet->_handRect.size.width/2.0f,
                            pRet->_handRect.origin.y + pRet->_handRect.size.height/2.0f);
   pRet->_tossPoint = Point(pRet->_grabPoint.x, pRet->_grabPoint.y + 15.0f);
*/
   pRet->setScale(0.7);
   
/*
   DrawNode *ancNode = DrawNode::create();
   ancNode->drawDot(pRet->getAnchorPointInPoints(), 20, Color4F(Color3B::WHITE));
   pRet->addChild(ancNode, 0);
*/
   
   pRet->_grabPoint = pRet->getPosition();
   pRet->_tossPoint = Point(pRet->_grabPoint.x, pRet->_grabPoint.y + 20.0f);
   
   Point t1 = pRet->getPosition();
   Size s1 = pRet->getContentSize();
   Rect r1 = pRet->getRect1();
   
   DrawNode *dotNode = DrawNode::create();
   dotNode->drawDot(pRet->getPosition(), 10, Color4F(Color3B::WHITE));

   
   DrawNode *dotNode1 = DrawNode::create();
   Point p1 = r1.origin;
   p1.x += r1.size.width;
   Point p2 = p1;
   p2.y += r1.size.height;
   Point p3 = p2;
   p3.x = r1.origin.x;
   Point verts [] = {r1.origin,p1,p2,p3};
   dotNode1->drawPolygon(verts, 4, Color4F(1,222,120,0.2), 1.0, Color4F(Color3B::WHITE));
   //dotNode->drawDot(pRet->getPosition(), 10, Color4F(Color3B::WHITE));
   
   //(pRet->getPosition(), 10, Color4F(Color3B::WHITE));
   DrawNode *dotNode2 = DrawNode::create();
   p1 = pRet->getPosition();
   p1.x += pRet->getContentSize().width;
   p2 = p1;
   p2.y += pRet->getContentSize().height;
   p3 = p2;
   p3.x = pRet->getPosition().x;
   Point verts1 [] = {pRet->getPosition(),p1,p2,p3};
   dotNode2->drawPolygon(verts1, 4, Color4F(1,222,120,0.2), 1.0, Color4F(Color3B::WHITE));
   
   

   pRet->addChild(dotNode, 0);
   //pRet->addChild(dotNode1, 0);
   pRet->addChild(dotNode2, 0);
   
   

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
   //this->_grabPoint = Point(_handRect.origin.x + _handRect.size.width/2.0f,
   //                         _handRect.origin.y + _handRect.size.height/2.0f);
   
   Sprite::setPosition(aPosition);
   
   this->_grabPoint = this->getPosition();
   this->_tossPoint = Point(_grabPoint.x, _grabPoint.y + 15.0f);
   
}


void Hand::catchItem(Item* anItem)
{
   this->_catchItem = anItem;
   this->_grabPoint.y = _catchItem->getPosition().y;
   //this->_tossPoint.y = this->_grabPoint.y + 15.0f;
   
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
      currPos.y += 1.0f;
      _catchItem->setPosition(currPos);
      this->runHandUpAnimatedAction();
   }

}

Item* Hand::tossItem()
{
   Item* tossingItem = nullptr;
   if (!_catchItem) {
      return tossingItem;
   }
   Point currPos = _catchItem->getPosition();
   if (currPos.x >= _tossPoint.x - 1.0f &&
       currPos.x <= _tossPoint.x + 1.0f &&
       currPos.y == _tossPoint.y) {
      currPos.y += 1.0f;
      _catchItem->setPosition(currPos);
      this->runTossAmiatedAction();
      return this->dropItem();
   }
   
   return nullptr;
}

bool Hand::isHandBusy()
{
   Point currHandPos = this->getPosition();
   Point handPos = Point((_handRect.origin.x + _handRect.size.width / 2.0f), (_handRect.origin.y + _handRect.size.height / 2.0f));
   bool isHandBusy = (((handPos.x != currHandPos.x) || (handPos.y != currHandPos.y)) && (_catchItem) &&
   (this->getNumberOfRunningActions() > 0));
   return isHandBusy;
}

Rect Hand::getRect1()
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
   float duration = (pos.x - this->_grabPoint.x)/aConveyorVelocity;
   
   Animation* animation = this->getAnimation(1,2, (duration/2.0));
   //pos.x = _grabPoint.x;
   //pos.y = pos.y + _catchItem->getContentSize().height/2.0f;
   pos = Point(_handRect.origin.x + _handRect.size.width/2.0f,_handRect.origin.y + _handRect.size.height/2.0f);
   MoveTo* move1 = MoveTo::create(duration/2.0f,  pos);
   Point pos2 = Point(_grabPoint.x,_grabPoint.y + _catchItem->getScaledContentSize().height/2.0f);
   MoveTo* move2 = MoveTo::create(duration/2.0f, pos2);
   
   this->runAction(Spawn::create(Sequence::create(move1,move2, NULL),Animate::create(animation),NULL));

}

void Hand::runHandUpAnimatedAction()
{
   float duration = 0.5f;
   Point t = _catchItem->getPosition();
   Point currPos = this->getPosition();
   currPos.y += (_tossPoint.y - currPos.y);
   
   MoveTo* moveUp = MoveTo::create(duration, currPos); //_tossPoint
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

