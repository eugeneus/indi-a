
#include "Item.h"

USING_NS_CC;

bool Item::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
    
    
    return true;
}