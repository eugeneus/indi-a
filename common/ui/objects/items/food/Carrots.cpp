
#include "Carrots.h"
#include "SoundsConstants.h"

USING_NS_CC;

Carrots* Carrots::create()
{
    Carrots *pRet = new Carrots();
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

bool Carrots::init() {
    
    if(!super::init("carrots_1.png", "carrots_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 8;
    return true;
}