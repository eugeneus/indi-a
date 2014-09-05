
#include "Duck.h"
#include "SoundsConstants.h"


USING_NS_CC;

Duck* Duck::create()
{
    Duck *pRet = new Duck();
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

bool Duck::init() {
    
    if(!super::init("duck_1.png", "duck_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 2;
    _crashSoundFile = SOUND_FALL_DUCK;
    return true;
}

FiniteTimeAction* Duck::getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
    Point endPoint = Point(aStartPoint.x + (100.0f * anImpulse.x), aStartPoint.y + (100.0f * anImpulse.y));
    FiniteTimeAction* moveTo = MoveTo::create(aTimeInterval, endPoint);
    return moveTo;
    
}