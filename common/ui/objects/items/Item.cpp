
#include "Item.h"

USING_NS_CC;

bool Item::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
   
   _defaultScale = 0.7;
    
    return true;
}

FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point anImpulse)
{
   return nullptr;
}
