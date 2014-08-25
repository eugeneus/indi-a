
#include "Spice.h"

USING_NS_CC;

Spice* Spice::create()
{
    Spice *pRet = new Spice();
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

bool Spice::init() {
    
    if(!super::init("item_bonus_2.png", "item_bonus_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 15;
    return true;
}