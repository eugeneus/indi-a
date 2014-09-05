
#include "Lemon.h"
#include "SoundsConstants.h"

USING_NS_CC;

Lemon* Lemon::create()
{
    Lemon *pRet = new Lemon();
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

bool Lemon::init() {
    
    if(!super::init("item_bonus_3.png", "item_bonus_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 13;
    return true;
}