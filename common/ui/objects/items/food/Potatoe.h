
#ifndef __BlindChef__Potatoe__
#define __BlindChef__Potatoe__

#include "cocos2d.h"
#include "Food.h"

class Potatoe : public Food {
public:
    static Potatoe* create();
    
    bool init();
    virtual void runBounceAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType);
    //virtual void setIdle(cocos2d::Point anIdleItemPosition);
    //virtual void stopActions();
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Potatoe__) */
