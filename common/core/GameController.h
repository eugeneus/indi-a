
#ifndef __BlindChef__GameController__
#define __BlindChef__GameController__


#include "cocos2d.h"
USING_NS_CC;

class Item;
class Chef;
class Pot;

class GameController : public cocos2d::Ref {

public:

   GameController();

   ~GameController();

   static GameController* createWitLayer(cocos2d::Layer* aGameLayer);

   bool initWithLayer(cocos2d::Layer* aGameLayer);
   
   void startGame();
   
   void stopGame();
   
   void update(float dt);

protected:
   
   void arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
   
   void populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
   
   void startLinearMove(Item* anItem);
   void tryPutNextItem(float dt, Item* anItem);
   void setItemIdle(float dt, Item* anItem);

   void throwItemSimple(Item* anItem, float throwX, Vec2 anImpulse);
   FiniteTimeAction* bounceItemAction(Item* anItem, float aWeight, Vec2 anImpulse);
   // model
   cocos2d::Vector<cocos2d::Node*>* _items;
   cocos2d::PointArray* _points;
   
   float _convY;
   float _convVelY;
   float _convLegth;
   float _putNextItemDt;
   float _itemTimer;

   cocos2d::Vec2 _itemIdlePos;
   int _idxRotated;
   
   Pot* _thePot;
   Chef* _theChef;
   
private:
   
   cocos2d::Layer* _gameLayer;

};
#endif /* defined(__BlindChef__GameController__) */
