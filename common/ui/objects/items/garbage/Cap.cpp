
#include "Cap.h"

USING_NS_CC;

Cap* Cap::create()
{
    Cap *pRet = new Cap();
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

bool Cap::init() {
    
    if(!super::init("cap_1.png", "cap_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.01;
    _bounceRatio = 0.01;
    _itemId = 4;
    
    return true;
}

FiniteTimeAction* Cap::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    return DelayTime::create(0.1);
}

FiniteTimeAction* Cap::getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Point currentPoint = this->getPosition();
    float _duration = aDuration*2;
    
    float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
    _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
    _currentTargetType = 1; // fall on floor
    
    FiniteTimeAction* moveAction = MoveTo::create(_duration, _currentTargetPoint);
    
    RotateTo* r1 = RotateTo::create(_duration/6.0f, 20.0f);
    RotateTo* r2 = RotateTo::create(_duration/6.0f, -20.0f);
    RotateTo* r3 = RotateTo::create(_duration/6.0f, 0.0f);
    
    Sequence* rt = Sequence::create(r1, r2, r3, NULL);
    // Repeat* repeatedRotation = Repeat::create(rt, 4);
    
    FiniteTimeAction* combinedAction = Spawn::create(moveAction, rt, NULL);
    
    return combinedAction;
    
}