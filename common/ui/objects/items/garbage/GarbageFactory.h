

#ifndef __BlindChef__GarbageFactory__
#define __BlindChef__GarbageFactory__

#include "Garbage.h"

enum
{
    kGarbageBottle = 0,
    kGarbageBowlingBall,
    kGarbageDuck
};

class GarbageFactory {
    
public:
    static Garbage* createGarbage(int garbage_type);
};

#endif /* defined(__BlindChef__GarbageFactory__) */
