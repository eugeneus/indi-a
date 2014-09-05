
#include "Salt.h"
#include "SoundsConstants.h"

USING_NS_CC;

Salt* Salt::create()
{
    Salt *pRet = new Salt();
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

bool Salt::init() {
    
    if(!super::init("item_bonus_1.png", "item_bonus_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 14;
    return true;
}