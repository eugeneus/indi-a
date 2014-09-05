
#include "Garglic.h"
#include "SoundsConstants.h"

USING_NS_CC;

Garglic* Garglic::create()
{
    Garglic *pRet = new Garglic();
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

bool Garglic::init() {
    
    if(!super::init("garglic_1.png", "garglic_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 2;
    return true;
}