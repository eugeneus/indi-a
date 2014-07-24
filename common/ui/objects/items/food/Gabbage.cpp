
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

FiniteTimeAction* Gabbage::getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
   Point endPoint = Point(aStartPoint.x + (100.0f * anImpulse.x), aStartPoint.y + (100.0f * anImpulse.y));
   float jumpHeight = (50.0f * anImpulse.y);
   int jumpsCount = 2;
   FiniteTimeAction* jump = JumpTo::create(aTimeInterval, endPoint, jumpHeight, jumpsCount);
   return jump;
}