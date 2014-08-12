
#include "Bread.h"

USING_NS_CC;

Bread* Bread::create()
{
    Bread *pRet = new Bread();
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

bool Bread::init() {
    
    if(!super::init("bread_1.png", "bread_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.5;
    _bounceRatio = 0.3;
    _itemId = 10;
    return true;
}