
#include "Egg.h"


USING_NS_CC;

Egg* Egg::create()
{
    Egg *pRet = new Egg();
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

bool Egg::init() {
    
    if(!super::init("egg_1.png", "egg_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.0;
    _itemId = 6;
    return true;
}