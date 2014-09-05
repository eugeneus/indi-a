
#include "Chicken.h"
#include "SoundsConstants.h"

USING_NS_CC;

Chicken* Chicken::create()
{
    Chicken *pRet = new Chicken();
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

bool Chicken::init() {
    
    if(!super::init("chicken_1.png", "chicken_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.5;
    _bounceRatio = 0.2;
    _itemId = 4;
    return true;
}