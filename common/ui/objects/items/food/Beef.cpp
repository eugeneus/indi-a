
#include "Beef.h"
#include "SoundsConstants.h"

USING_NS_CC;

Beef* Beef::create()
{
    Beef *pRet = new Beef();
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

bool Beef::init() {
    
    if(!super::init("beef_1.png", "beef_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.6;
    _bounceRatio = 0.0;
    _itemId = 12;
    
    _crashSoundFile = SOUND_FALL_MEAT;
    return true;
}

cocos2d::FiniteTimeAction* Beef::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 1; i < 9; i++)
    {
        sprintf(frameName, "beef_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}
