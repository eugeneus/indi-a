
#ifndef __BlindChef__Tomato__
#define __BlindChef__Tomato__

#include "cocos2d.h"
#include "Food.h"

class Tomato : public Food {
public:
    static Tomato* create();
    
    bool init();
    
    virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
    virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
    
    virtual void setIdle(cocos2d::Point anIdleItemPosition) override;
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Tomato__) */
