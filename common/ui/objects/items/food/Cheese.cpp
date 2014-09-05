
#include "Cheese.h"
#include "SoundsConstants.h"

USING_NS_CC;

Cheese* Cheese::create()
{
    Cheese *pRet = new Cheese();
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

bool Cheese::init() {
    
    if(!super::init("cheese_1.png", "cheese_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.4;
    _bounceRatio = 0.3;
    _itemId = 11;
    return true;
}