
#ifndef __BlindChef__Pants__
#define __BlindChef__Pants__

#include "cocos2d.h"
#include "Garbage.h"

class Pants : public Garbage {
private:
    typedef Garbage super;
public:
    static Pants* create();
    
    bool init();
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse) override;
};

#endif /* defined(__BlindChef__Pants__) */
