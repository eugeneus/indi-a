
#include "Potatoe.h"
#include "SoundsConstants.h"

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

cocos2d::FiniteTimeAction* Potatoe::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 2; i < 9; i++)
    {
        sprintf(frameName, "potatoe_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}

