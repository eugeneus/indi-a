

#ifndef __BlindChef__GarbageFactory__
#define __BlindChef__GarbageFactory__

#include "Garbage.h"

enum
{
    kGarbageBottle = 0,
    kGarbageBowlingBall,
    kGarbageDuck,
    kGarbagePants,
    kGarbageCap,
    kGarbageMobile,
    kGarbageSocks,  //TODO: add
    kGarbageGlasses, //TODO: ADD
    kGarbageHairbrush //TODO: add
};

class GarbageFactory {
    
public:
    static Garbage* createGarbage(int garbage_type);
};

#endif /* defined(__BlindChef__GarbageFactory__) */
