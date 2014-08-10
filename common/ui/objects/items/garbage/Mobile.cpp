
#include "Mobile.h"

USING_NS_CC;

Mobile* Mobile::create()
{
    Mobile *pRet = new Mobile();
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

bool Mobile::init() {
    
    if(!super::init("mobile_1.png", "mobile_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.3;
    _bounceRatio = 0.1;
    _itemId = 5;
    
    return true;
}

FiniteTimeAction* Mobile::getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
    Point endPoint = Point(aStartPoint.x + (100.0f * anImpulse.x), aStartPoint.y + (100.0f * anImpulse.y));
    FiniteTimeAction* moveTo = MoveTo::create(aTimeInterval, endPoint);
    return moveTo;
    
}