
#include "Gabbage.h"
#include "SoundsConstants.h"

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
    
    if(!super::init("cabbage_1.png", "cabbage_%i.png", 2, 0.2)) {
        return false;
    }
   _weightRatio = 0.5;
   _bounceRatio = 0.2;
    _itemId = 0;
    return true;
}

cocos2d::FiniteTimeAction* Gabbage::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 1; i < 10; i++)
    {
        sprintf(frameName, "cabbage_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}


