
#ifndef __BlindChef__Potatoe__
#define __BlindChef__Potatoe__

#include "cocos2d.h"
#include "Food.h"

class Potatoe : public Food {
public:
    static Potatoe* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Potatoe__) */
