
#include "Item.h"

USING_NS_CC;

bool Item::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
   
   _defaultScale = 1.0;
    
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

// based on predefined end points
ccBezierConfig Item::bezierConfigTouchPathToEndPoint(Point anEndPoint, Vec2 anImpulse)
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

cocos2d::FiniteTimeAction* Item::getConveyourAction(float aDuration, cocos2d::Point anEndPoint)
{

   this->_currentTargetPoint = anEndPoint;
   this->_currentTargetType = 0;
   
   FiniteTimeAction* actionMove = MoveTo::create(aDuration,anEndPoint);
   // add action to
   actionMove->setTag(1001);
   
   return actionMove;
   
}


cocos2d::FiniteTimeAction* Item::getTossAction(float aDuration, cocos2d::Point anEndPoint,
                                               int aCollisionType, cocos2d::Point anImpulse)
{
   this->stopActionByTag(1001);
   
   this->_currentTargetPoint = anEndPoint;
   this->_currentTargetType = aCollisionType;
   
   ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(anEndPoint, anImpulse);
   BezierTo* bezierBounceAction = BezierTo::create(aDuration, bouncePathConfig);
   
   RotateTo* r1 = RotateTo::create(aDuration/9.0f, 120.0f);
   RotateTo* r2 = RotateTo::create(aDuration/9.0f, 240.0f);
   RotateTo* r3 = RotateTo::create(aDuration/9.0f, 360.0f);
   
   Sequence* rt = Sequence::create(r1, r2, r3, NULL);
   Repeat* repeated = Repeat::create(rt, 3);

   FiniteTimeAction* fullAction = NULL;
   fullAction =  Sequence::create(bezierBounceAction,
                                  NULL);
   
   FiniteTimeAction* combinedAction = Spawn::create(fullAction, repeated, NULL);
   
   return combinedAction;
   
}

cocos2d::FiniteTimeAction* Item::getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse)
{
   
   // 1 next EndPoint calc
   Point currentPoint = this->getPosition();
   
   float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
   _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
   _currentTargetType = 1; // fall on floor
   // calc path
   ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(_currentTargetPoint, anImpulse);
   FiniteTimeAction* moveAction = BezierTo::create(aDuration, bouncePathConfig);

   RotateTo* r1 = RotateTo::create(aDuration/12.0f, 120.0f);
   RotateTo* r2 = RotateTo::create(aDuration/12.0f, 240.0f);
   RotateTo* r3 = RotateTo::create(aDuration/12.0f, 360.0f);
   
   Sequence* rt = Sequence::create(r1, r2, r3, NULL);
   Repeat* repeatedRotation = Repeat::create(rt, 4);
   
   FiniteTimeAction* combinedAction = Spawn::create(moveAction, repeatedRotation, NULL);
   
   return combinedAction;
}

cocos2d::FiniteTimeAction* Item::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
   
   Point currentPoint = this->getPosition();
   
   float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
   _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
   _currentTargetType = 1;
   // calc path
   float jumpHeight = (50.0f * anImpulse.y);
   int jumpsCount = 2;
   FiniteTimeAction* jumpAction = JumpTo::create(aDuration, _currentTargetPoint, jumpHeight, jumpsCount);

   RotateTo* r1 = RotateTo::create(aDuration/6.0f, 60.0f);
   RotateTo* r2 = RotateTo::create(aDuration/6.0f, 0.0f);
   Sequence* rt = Sequence::create(r1, r2, NULL);

   Repeat* repeatedRotation = Repeat::create(rt, 2);

   FiniteTimeAction* combinedAction = Spawn::create(jumpAction, repeatedRotation, NULL);
   
   return combinedAction;
   
}

cocos2d::FiniteTimeAction* Item::getFingerKickAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse)
{
   
   return nullptr;
   
}

cocos2d::FiniteTimeAction* Item::getVanishAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse)
{
   
   _currentTargetPoint = _idleItemPosition;
   _currentTargetType = 0;
   
   FiniteTimeAction* actionDelay = DelayTime::create(2);
   FiniteTimeAction* actionPlase = Place::create(_idleItemPosition);
   FiniteTimeAction* actionFadeOut = FadeOut::create(2);
   FiniteTimeAction* actionFadeIn = FadeIn::create(2);
   
   FiniteTimeAction* fullAction = Sequence::create(actionFadeOut, //actionDelay,
                                                   actionPlase,
                                                   actionFadeIn,
                                                   NULL);

   return fullAction;
   
}

bool Item::isItemInCurrentTargetPoint()
{
   Point currPos = this->getPosition();
   
   return _currentTargetPoint.equals(this->getPosition());

}

void Item::runTouchAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType)
{
    
    this->stopActionByTag(1001);
    
    ccBezierConfig bouncePathConfig = this->bezierConfigTouchPathToEndPoint(anEndPoint, anImpulse);
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
    FiniteTimeAction* scaleBy1 = cocos2d::ScaleBy::create(2*durationPart, this->getScale());
    FiniteTimeAction* scaleRev1 = scaleBy1->reverse();
    FiniteTimeAction* scaleBy2 = cocos2d::ScaleBy::create(0.2f, 0.8f);
    FiniteTimeAction* scaleRev2 = scaleBy2->reverse();
   // scaleRev1->setDuration(0.1);
    scaleRev2->setDuration(0.1);
    
    FiniteTimeAction* act = Sequence::create(scaleRev1, scaleBy2,scaleRev2,NULL);
    this->runAction(Spawn::create(fullAction, act,NULL));
}

void Item::setIdle(cocos2d::Point anIdleItemPosition)
{
   this->_idleItemPosition = anIdleItemPosition;
   this->setPosition(_idleItemPosition);
   this->stopAllActions();
   this->setDefaultSize();
   this->setOpacity(255);
   
}

void Item::stopActions()
{
   this->stopAllActions();
   this->setDefaultSize();
   
}

Sprite* Item::createCrack() {
    return NULL;
}



