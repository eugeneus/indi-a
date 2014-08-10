
#ifndef __BlindChef__Cap__
#define __BlindChef__Cap__

#include "cocos2d.h"
#include "Garbage.h"

class Cap : public Garbage {
private:
    typedef Garbage super;
public:
    static Cap* create();
    
    bool init();
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse) override;
};

#endif /* defined(__BlindChef__Cap__) */
