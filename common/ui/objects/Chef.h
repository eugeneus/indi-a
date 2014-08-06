
#ifndef __BlindChef__Chef__
#define __BlindChef__Chef__

#include "cocos2d.h"
#include "Spritable.h"

class Item;

class Chef  {
public:
   Chef();
   ~Chef();
    static Chef* create(cocos2d::Layer* aLayer, int aZOrder);
    
    bool init(cocos2d::Layer* aLayer, int aZOrder);
 
   void setScale(float aScaleFactor);
   cocos2d::Size getSize();
   void setOrigin(cocos2d::Point anOrigin);
   void setWatchSector(cocos2d::Size aSectroSize);
   void setConveyorVelocity(float aConveyorVelocity);
   
   cocos2d::Point getActiveBouncePoint();
   cocos2d::Vec2 getBounceImpulse();
   
   void startChefBodyAnimation();
   void startHandBounceAnimation();
   bool tryToCatchItem(Item* anItem, float aConveyorVelocity);
   void chefWathItem(Item* anItem);
   void setZOrder(int aZOrder);
protected:
   void updateBounceImpulse();
   void runGrabAnimation(cocos2d::Sprite* activeHand, cocos2d::Point itemPos, cocos2d::Rect activeHandRect);
   cocos2d::Animate* getHandGrabAnimation();
   
private:
   //typedef cocos2d::Ref super;
   cocos2d::Rect _chefRect;
   
   cocos2d::Vec2 _bounceImpulse;
   cocos2d::Rect _leftHandRect;
   cocos2d::Rect _rightHandRect;
   
   cocos2d::Layer* _layer;
   cocos2d::Sprite* _chef;
   cocos2d::Sprite* _leftHand;
   cocos2d::Sprite* _rightHand;
   
   cocos2d::Size _szWatchSector;
   cocos2d::Point _activeBouncePoint;
   int _sleepCounter;
   float _conveyorVelocity;
   
};

#endif /* defined(__BlindChef__Chef__) */
