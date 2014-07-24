
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

FiniteTimeAction* Bottle::getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse)
{
   /*
   Vector<SpriteFrame*> animateFrames(6);
   char frameName[100] = {0};
   SpriteFrame* animFrame = nullptr;
   
   for(int i = 1; i < 7; i++)
   {
      sprintf(frameName, "bottle_crash_%1d.png", i);
      animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
      animateFrames.pushBack(animFrame);
      animFrame->release();
   }
   Animation* a = Animation::createWithSpriteFrames(animateFrames, 0.3f);
   a->autorelease();
    */
   return nullptr;
}