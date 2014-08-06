
#include "Tomato.h"


USING_NS_CC;

Tomato* Tomato::create()
{
    Tomato *pRet = new Tomato();
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

bool Tomato::init() {
    
    if(!super::init("tomato_1.png", "tomato_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    
    return true;
}