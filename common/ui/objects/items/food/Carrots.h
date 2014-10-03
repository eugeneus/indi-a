
#ifndef __BlindChef__Carrots__
#define __BlindChef__Carrots__

#include "cocos2d.h"
#include "Food.h"

class Carrots : public Food {
public:
    static Carrots* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Carrots__) */
