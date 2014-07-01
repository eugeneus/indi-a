
#include "GarbageFactory.h"
#include "Bottle.h"

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
            
        default:
        {
            garbage = NULL;
            break;
        }
    }
    return garbage;
}