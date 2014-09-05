
#include "Onion.h"
#include "SoundsConstants.h"

USING_NS_CC;

Onion* Onion::create()
{
    Onion *pRet = new Onion();
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

bool Onion::init() {
    
    if(!super::init("onion_1.png", "onion_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 7;
    return true;
}