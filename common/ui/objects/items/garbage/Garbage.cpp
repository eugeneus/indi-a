
#include "Garbage.h"
#include "SoundsConstants.h"

USING_NS_CC;

bool Garbage::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::init(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
    
    _itemType = 1;
    _hitPotSoundFileName = SOUND_POT_FALL_GARBAGE;
    return true;
}