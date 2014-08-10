
#ifndef __BlindChef__Mobile__
#define __BlindChef__Mobile__

#include "cocos2d.h"
#include "Garbage.h"

class Mobile : public Garbage {
private:
    typedef Garbage super;
public:
    static Mobile* create();
    
    bool init();
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse);
};

#endif /* defined(__BlindChef__Mobile__) */
