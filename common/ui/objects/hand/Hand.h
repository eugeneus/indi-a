
#ifndef __BlindChef__Hand__
#define __BlindChef__Hand__

#include "cocos2d.h"

class Item;

class Hand : public cocos2d::Sprite {
public:
   
   Hand();
   ~Hand();

   static Hand* create(const std::string &aSpriteFrameName);
    
   void mirrorImg();
   
   void setInitialPosition(cocos2d::Point aPosition);

   void catchItem(Item* anItem);
   
   void setIgnoredItem(Item* anItem);
   
   bool isIgnoredItem(Item* anItem);
   
   bool isCaughtItem(Item* anItem);
   
   Item* dropItem();
   
   void upItem();
   
   Item* tossItem();
   
   bool isHandBusy();
    
    bool isHandIdle();
   
   bool isCanGrabItem(Item* anItem);
   
   cocos2d::Rect getRect1();
   
   bool randomWaitForToss();
   
   void runGrabAnimatedAction(float aConveyorVelocity);
    
    void restart();
protected:

   void runHandUpAnimatedAction();
   void runTossAmiatedAction();
   
   cocos2d::Animation* getAnimation(int aFirtsImageIndex, int aLastImageIndex, float aDelay);
   //bool waitIgnoredItem();
   float getRandomFloat(float from ,float to);
   
   void testDraw();
   
   Item* _catchItem;
   
   Item* _ignoredItem;
   
   cocos2d::Rect _handRect;
   cocos2d::Point _tossPoint;
   cocos2d::Point _grabPoint;
   

private:
   //typedef Layer super;
   //cocos2d::Sprite* handImg;
};

#endif /* defined(__BlindChef__Hand__) */
