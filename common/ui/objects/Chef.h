
#ifndef __BlindChef__Chef__
#define __BlindChef__Chef__

#include "cocos2d.h"
#include "Spritable.h"

class Item;
class Hand;

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
    void startChefHeadIdleAnimation();
   
   Item* looksForItem(Item* anItem, float aConveyourVelocity);
   void setZOrder(int aZOrder);
    
    // eyesight control
    void setVision(std::vector<int> aRequiredItems);
    void resetVision();
    bool hasVision();
    bool isRequiredItem(Item* anItem);
   
    void restartChef();
    
    bool isChefIdle();

protected:
   
   bool isItemAccesible(Item* anItem);
   bool isHandCanGrab(Hand* aHand, Item* anItem);
    bool isHandShouldGrabItem(Hand* aHand, Item *anItem);
   void updateBounceImpulse();
    
    //void resetHands();
   
private:
   //typedef cocos2d::Ref super;
   cocos2d::Rect _chefRect;
   
   cocos2d::Vec2 _bounceImpulse;
   cocos2d::Rect _leftHandRect; // obsolete?
   cocos2d::Rect _rightHandRect; // obsolete?
   
   cocos2d::Layer* _layer;
   cocos2d::Sprite* _chef;
    cocos2d::Sprite* _head;
   Hand* _leftHand;
   Hand* _rightHand;
   
   cocos2d::Size _szWatchSector;
   cocos2d::Point _activeBouncePoint;
   int _sleepCounter;
   float _conveyorVelocity;
    std::vector<int> _requiredItemIDs;
   
};

#endif /* defined(__BlindChef__Chef__) */
