
#include "BowlingBall.h"

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
    
    
    return true;
}