
#include "GarbageFactory.h"
#include "Bottle.h"
#include "BowlingBall.h"
#include "Duck.h"
#include "Pants.h"
#include "Cap.h"
#include "Mobile.h"

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
        case kGarbageDuck:
        {
            garbage = Duck::create();
            break;
        }
        case kGarbagePants:
        {
            garbage = Pants::create();
            break;
        }
        case kGarbageCap:
        {
            garbage = Cap::create();
            break;
        }
        case kGarbageMobile:
        {
            garbage = Mobile::create();
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