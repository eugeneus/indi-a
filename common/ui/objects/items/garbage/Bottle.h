
#ifndef __BlindChef__Bottle__
#define __BlindChef__Bottle__

#include "cocos2d.h"
#include "Garbage.h"

class Bottle : public Garbage {
private:
    typedef Garbage super;
public:
    static Bottle* create();
    
   bool init();
   
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse) override;
   
   virtual void setIdle(cocos2d::Point anIdleItemPosition) override;
   
   cocos2d::FiniteTimeAction* getFloorBumpAnimation(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse);
};


#endif /* defined(__BlindChef__Bottle__) */
