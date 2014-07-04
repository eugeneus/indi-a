
#include "Pot.h"

USING_NS_CC;

Pot* Pot::create()
{
    Pot *pRet = new Pot();
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

bool Pot::init() {
    
    if(!Layer::init()) {
        return false;
    }
 
    front = Sprite::createWithSpriteFrameName("pot_front_1.png");
    front->setAnchorPoint(Vec2(0,0));
    this->addChild(front, 1);
    
    back = Sprite::createWithSpriteFrameName("pot_back_1.png");
    back->setAnchorPoint(Vec2(0,0));
    this->addChild(back, -1);
    
    this->setAnchorPoint(Vec2(0,0));
    
    return true;
}

