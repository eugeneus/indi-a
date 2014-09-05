
#include "BowlingBall.h"
#include "SoundsConstants.h"

USING_NS_CC;

BowlingBall* BowlingBall::create()
{
    BowlingBall *pRet = new BowlingBall();
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

bool BowlingBall::init() {
    
    if(!super::init("bowling_ball_1.png", "bowling_ball_%i.png", 1, 0.2)) {
        return false;
    }
   _weightRatio = 0.9;
   _bounceRatio = 0.5;
    _itemId = 1;
    
    _crashSoundFile = SOUND_FALL_BOWLING;
   
    return true;
}

FiniteTimeAction* BowlingBall::getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
   Point endPoint = Point(aStartPoint.x + (100.0f * anImpulse.x), aStartPoint.y + (100.0f * anImpulse.y));
   FiniteTimeAction* moveTo = MoveTo::create(aTimeInterval, endPoint);
   return moveTo;

}

Sprite* BowlingBall::createCrack() {
    return Sprite::createWithSpriteFrameName("bowling_ball_crack_land_1.png");
}