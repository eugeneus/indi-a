
#ifndef __BlindChef__MovementController__
#define __BlindChef__MovementController__

#include "cocos2d.h"

USING_NS_CC;

class Item;
//class cocos2d::BezierTo;

class MovementController { // obsolete

private:

protected:
   
   cocos2d::Vector<cocos2d::Action*>  _pathActions;
   cocos2d::Vector<Item*>  _items;
   
   float _grabPosX;
   
   BezierTo* createBezierPath(Vec2 aStartPos);
   void createFallenPathArray();
   void processThrowAction();

public:

   MovementController();

   ~MovementController();

   static MovementController* create();

   bool init();
   
   void addItem(Item& anItem);
   
   
   void update(float dt);


};
#endif /* defined(__BlindChef__MovementController__) */
