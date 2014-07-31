
#ifndef __BlindChef__Item__
#define __BlindChef__Item__

#include "cocos2d.h"
#include "Spritable.h"

class Item : public Spritable {
public:
    
   bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);

   virtual cocos2d::FiniteTimeAction* runConveyourAction(float aDuration, cocos2d::Point anEndPoint);
   
   virtual cocos2d::FiniteTimeAction* runTossAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* runFingerKickAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* runVanishAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual void runBounceAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType);
   virtual void runTouchAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType);
   
   virtual void setIdle(cocos2d::Point anIdleItemPosition);
   virtual void stopActions();
   //   virtual void initializeMenu();
   float _weightRatio;
   float _bounceRatio;
   cocos2d::Point _idleItemPosition;
protected:
   cocos2d::ccBezierConfig bezierConfigBouncePathToEndPoint(cocos2d::Point anEndPoint,
                                                            cocos2d::Vec2 anImpulse);
    cocos2d::ccBezierConfig bezierConfigTouchPathToEndPoint(cocos2d::Point anEndPoint, cocos2d::Vec2 anImpulse);
private:
   typedef Spritable super;
   
};

#endif /* defined(__BlindChef__Item__) */
