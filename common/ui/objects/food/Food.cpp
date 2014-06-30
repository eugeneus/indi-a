
#include "Food.h"

USING_NS_CC;

bool Food::initWithSpriteAndPos(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
    
    
    return true;
}