
#ifndef __BlindChef__Gabbage__
#define __BlindChef__Gabbage__

#include "cocos2d.h"
#include "Food.h"

class Gabbage : public Food {
private:
    typedef Food super;
public:
    static Gabbage* create();
    
    bool init();
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point anImpulse);
};


#endif /* defined(__BlindChef__Gabbage__) */
