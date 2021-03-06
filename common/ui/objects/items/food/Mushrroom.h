
#ifndef __BlindChef__Mushrroom__
#define __BlindChef__Mushrroom__

#include "cocos2d.h"
#include "Food.h"

class Mushrroom : public Food {
public:
    static Mushrroom* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Mushrroom__) */
