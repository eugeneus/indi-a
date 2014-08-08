
#include "Garbage.h"

USING_NS_CC;

bool Garbage::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::init(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
    
    _itemType = 1;
    return true;
}