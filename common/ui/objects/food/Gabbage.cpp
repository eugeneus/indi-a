
#include "Gabbage.h"

USING_NS_CC;

Gabbage* Gabbage::create()
{
    Gabbage *pRet = new Gabbage();
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

bool Gabbage::init() {
    
    if(!super::initWithSpriteAndPos("cabbage_1.psd", "cabbage_%i.psd", 1, 0.9)) {
        return false;
    }
    
    
    return true;
}