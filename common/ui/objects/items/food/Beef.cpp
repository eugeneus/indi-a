
#include "Beef.h"

USING_NS_CC;

Beef* Beef::create()
{
    Beef *pRet = new Beef();
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

bool Beef::init() {
    
    if(!super::init("beef_1.png", "beef_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.6;
    _bounceRatio = 0.0;
    _itemId = 12;
    return true;
}