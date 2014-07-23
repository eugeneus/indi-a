
#ifndef __BlindChef__Item__
#define __BlindChef__Item__

#include "cocos2d.h"
#include "Spritable.h"

class Item : public Spritable {
public:
    
   bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
   
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aTimeInterval, cocos2d::Point aStartPoint, cocos2d::Point anImpulse);
   //   virtual void initializeMenu();
   float _weightRatio;
   float _bounceRatio;
private:
   typedef Spritable super;
   
};

#endif /* defined(__BlindChef__Item__) */
