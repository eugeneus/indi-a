
#ifndef __BlindChef__Gabbage__
#define __BlindChef__Gabbage__

#include "cocos2d.h"
#include "Food.h"

class Gabbage : public Food {
public:
    static Gabbage* create();
    
    bool init();
   virtual void runBounceAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType);
   //virtual void setIdle(cocos2d::Point anIdleItemPosition);
   //virtual void stopActions();

private:
   typedef Food super;

};


#endif /* defined(__BlindChef__Gabbage__) */
