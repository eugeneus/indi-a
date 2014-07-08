
#include "GarbageFactory.h"
#include "Bottle.h"
#include "BowlingBall.h"

Garbage* GarbageFactory::createGarbage(int garbage_type)
{
    Garbage* garbage;
    switch(garbage_type)
    {
        case kGarbageBottle:
        {
            garbage = Bottle::create();
            break;
        }
        case kGarbageBowlingBall:
        {
            garbage = BowlingBall::create();
            break;
        }
            
        default:
        {
            garbage = Bottle::create();
            break;
        }
    }
    return garbage;
}