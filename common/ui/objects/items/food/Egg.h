
#ifndef __BlindChef__Egg__
#define __BlindChef__Egg__

#include "cocos2d.h"
#include "Food.h"

class Egg : public Food {
public:
    static Egg* create();
    
    bool init();
   
   virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse) override;
   
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
   
   virtual void setIdle(cocos2d::Point anIdleItemPosition) override;
   
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Egg__) */
