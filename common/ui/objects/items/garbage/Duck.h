
#ifndef __BlindChef__Duck__
#define __BlindChef__Duck__


#include "cocos2d.h"
#include "Garbage.h"

class Duck : public Garbage {
private:
    typedef Garbage super;
public:
    static Duck* create();
    
    bool init();
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse);
};

#endif /* defined(__BlindChef__Duck__) */
