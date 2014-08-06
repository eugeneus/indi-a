
#include "Potatoe.h"

USING_NS_CC;

Potatoe* Potatoe::create()
{
    Potatoe *pRet = new Potatoe();
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

bool Potatoe::init() {
    
    if(!super::init("potatoe_1.png", "potatoe_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.2;
    _itemId = 1;
    return true;
}