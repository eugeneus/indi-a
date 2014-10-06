
#ifndef __BlindChef__Gabbage__
#define __BlindChef__Gabbage__

#include "cocos2d.h"
#include "Food.h"

class Gabbage : public Food {
public:
    static Gabbage* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;

private:
   typedef Food super;

};


#endif /* defined(__BlindChef__Gabbage__) */
