
#include "Bottle.h"

USING_NS_CC;

Bottle* Bottle::create()
{
    Bottle *pRet = new Bottle();
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

bool Bottle::init() {
    
    if(!super::init("bottle_1.png", "bottle_%i.png", 1, 0.2)) {
        return false;
    }
   _weightRatio = 0.7;
   _bounceRatio = 0.5;
   
    return true;
}

FiniteTimeAction* Bottle::getFloorBumpAnimation(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
   
   Vector<SpriteFrame*> animateFrames(6);
   char frameName[100] = {0};
   SpriteFrame* animFrame = nullptr;
   
   for(int i = 1; i < 7; i++)
   {
      sprintf(frameName, "bottle_crash_%1d.png", i);
      animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
      animateFrames.pushBack(animFrame);
   }
   
   Animation* animation = Animation::createWithSpriteFrames(animateFrames, 0.3f);
   return Animate::create(animation);
}

FiniteTimeAction* Bottle::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
   Point pos = this->getPosition();
   FiniteTimeAction* action =getFloorBumpAnimation(aDuration/2.0f, pos, Point(0.0f,0.0f));
   return action;
}

void Bottle::setIdle(cocos2d::Point anIdleItemPosition)
{
   Item::setIdle(anIdleItemPosition);
   this->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bottle_1.png"));
}
