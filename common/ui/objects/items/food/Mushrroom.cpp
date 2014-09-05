
#include "Mushrroom.h"
#include "SoundsConstants.h"

USING_NS_CC;

Mushrroom* Mushrroom::create()
{
    Mushrroom *pRet = new Mushrroom();
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

bool Mushrroom::init() {
    
    if(!super::init("mushrroom_1.png", "mushrroom_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 9;
    return true;
}