
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
};

#endif /* defined(__BlindChef__BowlingBall__) */
