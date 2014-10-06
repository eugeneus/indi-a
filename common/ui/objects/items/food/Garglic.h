
#ifndef __BlindChef__Garglic__
#define __BlindChef__Garglic__

#include "cocos2d.h"
#include "Food.h"

class Garglic : public Food {
public:
    static Garglic* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Garglic__) */
