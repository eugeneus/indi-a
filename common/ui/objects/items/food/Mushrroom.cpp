
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
    
    if(!super::init("mushroom_1.png", "mushroom_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 9;
    return true;
}

cocos2d::FiniteTimeAction* Mushrroom::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 2; i < 5; i++)
    {
        sprintf(frameName, "mushroom_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}
