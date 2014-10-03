
#include "Carrots.h"
#include "SoundsConstants.h"

USING_NS_CC;

Carrots* Carrots::create()
{
    Carrots *pRet = new Carrots();
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

bool Carrots::init() {
    
    if(!super::init("carrot_1.png", "carrot_%i.png", 1, 0.2)) {
        return false;
    }
    _weightRatio = 0.1;
    _bounceRatio = 0.1;
    _itemId = 8;
    return true;
}


cocos2d::FiniteTimeAction* Carrots::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;
    
    
    for(int i = 1; i < 14; i++)
    {
        sprintf(frameName, "carrot_%d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.1f);
    return Animate::create(animation);
    
}
