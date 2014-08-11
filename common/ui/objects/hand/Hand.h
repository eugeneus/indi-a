
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
   
   void setPosition(cocos2d::Point aPosition);
   void catchItem(Item* anItem);
   Item* dropItem();
   Item* tossItem();
   bool isHandBusy();
   cocos2d::Rect getRect();
   
   bool randomWaitForToss();
   
   void runGrabAnimatedAction(float aConveyorVelocity);
   void runTossAmiatedAction();
protected:
   
   cocos2d::Animation* getAnimation(int aFirtsImageIndex, int aLastImageIndex, float aDelay);
   bool waitIgnoredItem();
   float getRandomFloat(float from ,float to);
   
   Item* _catchItem;
   
   Item* _ignoredItem;
   
   cocos2d::Rect _handRect;
   cocos2d::Point _tossPoint;
   

private:
   //typedef Layer super;
   //cocos2d::Sprite* handImg;
};

#endif /* defined(__BlindChef__Hand__) */
