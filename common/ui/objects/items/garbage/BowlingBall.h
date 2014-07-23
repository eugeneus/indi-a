
#ifndef __BlindChef__BowlingBall__
#define __BlindChef__BowlingBall__

#include "cocos2d.h"
#include "Garbage.h"

class BowlingBall : public Garbage {
private:
    typedef Garbage super;
public:
    static BowlingBall* create();
    
    bool init();
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point anImpulse);
};

#endif /* defined(__BlindChef__BowlingBall__) */
