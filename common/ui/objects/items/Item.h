
#ifndef __BlindChef__Item__
#define __BlindChef__Item__

#include "cocos2d.h"
#include "Spritable.h"

class Item : public Spritable {
public:
    
   bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);

   virtual cocos2d::FiniteTimeAction* getConveyourAction(float aDuration, cocos2d::Point anEndPoint);
   
   virtual cocos2d::FiniteTimeAction* getTossAction(float aDuration, cocos2d::Point anEndPoint,
                                                    int aCollisionType, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getFloorBumpAction(float aDuration, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getFingerKickAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual cocos2d::FiniteTimeAction* getVanishAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse);
   
   virtual void runTouchAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse, int aCollisionType);
   
   virtual void setIdle(cocos2d::Point anIdleItemPosition);
   
   virtual void stopActions();
    
    virtual cocos2d::Sprite* createCrack();
   
   bool isItemInCurrentTargetPoint();
   
   float _weightRatio;
   float _bounceRatio;
   cocos2d::Point _idleItemPosition;
   cocos2d::Point _currentTargetPoint;
   int _currentTargetType;
protected:
   cocos2d::ccBezierConfig bezierConfigBouncePathToEndPoint(cocos2d::Point anEndPoint,
                                                            cocos2d::Vec2 anImpulse);
    cocos2d::ccBezierConfig bezierConfigTouchPathToEndPoint(cocos2d::Point anEndPoint, cocos2d::Vec2 anImpulse);
   
private:
   typedef Spritable super;
   
};

#endif /* defined(__BlindChef__Item__) */
