
#include "Food.h"

USING_NS_CC;

bool Food::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::init(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
    
    
    return true;
}