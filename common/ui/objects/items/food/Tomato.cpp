
#include "Tomato.h"
#include "SoundsConstants.h"


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
    _itemId = 3;
    return true;
}


cocos2d::FiniteTimeAction* Tomato::getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    
    // 1 next EndPoint calc
    Point currentPoint = this->getPosition();
    
    float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
    _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
    _currentTargetType = 1; // fall on floor
    // calc path
    ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(_currentTargetPoint, anImpulse);
    FiniteTimeAction* moveAction = BezierTo::create(aDuration, bouncePathConfig);
    
    RotateTo* r1 = RotateTo::create(aDuration/12.0f, 120.0f);
    RotateTo* r2 = RotateTo::create(aDuration/12.0f, 240.0f);
    RotateTo* r3 = RotateTo::create(aDuration/12.0f, 360.0f);
    
    Sequence* rt = Sequence::create(r1, r2, r3, NULL);
    Repeat* repeatedRotation = Repeat::create(rt, 4);
    
    FiniteTimeAction* combinedAction = Spawn::create(moveAction, repeatedRotation, NULL);
    
    return combinedAction;
}

cocos2d::FiniteTimeAction* Tomato::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
    Vector<SpriteFrame*> animateFrames(3);
    char frameName[100] = {0};
    SpriteFrame* animFrame = nullptr;

    
    for(int i = 1; i < 4; i++)
    {
        sprintf(frameName, "tomato_crash_%1d.png", i);
        animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        animateFrames.pushBack(animFrame);
    }
    
    //sprintf(frameName, "tomato_crash_%1d.png", 2);
    //animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    //animateFrames.pushBack(animFrame);
    
    Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.7f);
    return Animate::create(animation);
    
}

void Tomato::setIdle(cocos2d::Point anIdleItemPosition)
{
    Item::setIdle(anIdleItemPosition);
    this->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tomato_1.png"));
}
