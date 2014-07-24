
#ifndef __BlindChef__Garbage__
#define __BlindChef__Garbage__

#include "cocos2d.h"
#include "Item.h"

class Garbage : public Item {
private:
    typedef Item super;
public:
    
    bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    //   virtual void initializeMenu();
   //virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse);
    
};

#endif /* defined(__BlindChef__Garbage__) */
