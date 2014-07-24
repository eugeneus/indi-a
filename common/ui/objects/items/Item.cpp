
#include "Item.h"

USING_NS_CC;

bool Item::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
   
   _defaultScale = 0.7;
    
    return true;
}

// based on predefined end points
ccBezierConfig Item::bezierConfigBouncePathToEndPoint(Point anEndPoint, Vec2 anImpulse)
{
   ccBezierConfig bezier;
   Size visibleSize = Size(Director::getInstance()->getVisibleSize());
   Point itemPos = this->getPosition();
   Point cp1 = itemPos;
   
   // assume start point of impulse always (0,0)
   cp1.y = itemPos.y + ((visibleSize.height) * anImpulse.y);
   cp1.x = itemPos.x + ((anEndPoint.x - itemPos.x) * anImpulse.x);
   
   bezier.controlPoint_1 = cp1;
   bezier.controlPoint_2 = anEndPoint;
   bezier.endPosition = anEndPoint;
   
   return bezier;
   
}


void Item::runBounceAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType)
{

   this->stopActionByTag(1001);
   
   ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(anEndPoint, anImpulse);
   BezierTo* bezierBounceAction = nullptr; //BezierTo::create(aDuration, bouncePathConfig);
   //bounceAction->setTag(1);
   
   FiniteTimeAction* actionRotate = nullptr; // plaseholder rotate
   
   
   FiniteTimeAction* actionDelay = DelayTime::create(2);
   FiniteTimeAction* actionPlase = Place::create(_idleItemPosition);
   
   Point nextStartPoint = Point(anEndPoint);
   float durationPart = aDuration;
   Point endPoint = Point(anEndPoint);
   FiniteTimeAction* fullAction = NULL;
   FiniteTimeAction* jumpAction = NULL;
   
   
   if(aCollisionType == 1){ // 1 -  floor colizion
      durationPart = aDuration * 0.2f;
      float dir = nextStartPoint.x > 320.0f ? 1.0f : -1.0f;
      endPoint = Point(nextStartPoint.x + (100.0f * anImpulse.x * dir), nextStartPoint.y - (50.0f * anImpulse.y));
      float jumpHeight = (50.0f * anImpulse.y);
      int jumpsCount = 2;
      jumpAction = JumpTo::create(durationPart, endPoint, jumpHeight, jumpsCount);
      durationPart = aDuration - durationPart;
      bezierBounceAction = BezierTo::create(durationPart, bouncePathConfig);
      fullAction =  Sequence::create(bezierBounceAction,
                                     jumpAction,
                                     actionDelay,
                                     actionPlase,
                                     NULL);
   }
   else if(aCollisionType == 2){ // 2 - pot vertex collision
      
      float dir = nextStartPoint.x > 320.0f ? 1.0f : -1.0f;
      
      durationPart = aDuration * 0.2f;
      ccBezierConfig bezier;
      Point cp1;
      cp1.y = anEndPoint.y + 100.0f;
      cp1.x = anEndPoint.x + 100.0f * dir;
      
      Point cp2;
      cp2.y = anEndPoint.y - 600.0f;
      cp2.x = anEndPoint.x + 120.0f * dir;
      
      bezier.controlPoint_1 = cp1;
      bezier.controlPoint_2 = cp2;
      bezier.endPosition = cp2;
      BezierTo* bezierJumpAction = BezierTo::create(durationPart, bezier);
      
      durationPart = aDuration - durationPart;
      bezierBounceAction = BezierTo::create(durationPart, bouncePathConfig);
      
      fullAction =  Sequence::create(bezierBounceAction,bezierJumpAction,actionDelay,actionPlase, NULL);
      // create bounce anim as for #1
      // add another bezier for fall item out of Pot
   }
   else{ // center pot collision
      bezierBounceAction = BezierTo::create(durationPart, bouncePathConfig);
      fullAction =  Sequence::create(bezierBounceAction,actionPlase, NULL);
   }
   
   durationPart = durationPart - 0.7;
   FiniteTimeAction* scaleBy1 = cocos2d::ScaleBy::create(durationPart, 2.5f);
   FiniteTimeAction* scaleRev1 = scaleBy1->reverse();
   FiniteTimeAction* scaleBy2 = cocos2d::ScaleBy::create(0.5f, 0.8f);
   FiniteTimeAction* scaleRev2 = scaleBy2->reverse();
   scaleRev1->setDuration(0.1);
   scaleRev2->setDuration(0.1);
   
   FiniteTimeAction* act = Sequence::create(scaleBy1,scaleBy2,scaleRev1,scaleRev2,NULL);
   this->runAction(Spawn::create(fullAction, act,NULL));

   
}

void Item::setIdle(cocos2d::Point anIdleItemPosition)
{
   this->_idleItemPosition = anIdleItemPosition;
   this->setPosition(_idleItemPosition);
   this->stopAllActions();
   this->setDefaultSize();
   
}

void Item::stopActions()
{
   this->stopAllActions();
   this->setDefaultSize();
   
}



