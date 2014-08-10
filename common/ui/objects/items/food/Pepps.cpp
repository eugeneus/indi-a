
#include "Pepps.h"

USING_NS_CC;

Pepps* Pepps::create()
{
    Pepps *pRet = new Pepps();
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

bool Pepps::init() {
    
    if(!super::init("pepps_1.png", "pepps_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.2;
    _itemId = 5;
    return true;
}