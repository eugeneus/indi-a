
#include "Gabbage.h"

USING_NS_CC;

Gabbage* Gabbage::create()
{
    Gabbage *pRet = new Gabbage();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Gabbage::init() {
    
    if(!super::init("cabbage_1.png", "cabbage_%i.png", 2, 0.2)) {
        return false;
    }
   _weightRatio = 0.5;
   _bounceRatio = 0.2;
   
    return true;
}

// start poinn looks redundand float aStartPoint,
void Gabbage::runBounceAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType)
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
      cp2.y = anEndPoint.y - 100.0f;
      cp2.x = anEndPoint.x + 150.0f * dir;
      
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

   
   // rotate
   // screw
   
   // TODO: it would good to call setItem Idle thru Action CallBack
}


