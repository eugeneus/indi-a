
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

cocos2d::FiniteTimeAction* Garglic::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 2; i < 9; i++)
    {
        sprintf(frameName, "garglic_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}
