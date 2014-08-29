
#ifndef __BlindChef__GameController__
#define __BlindChef__GameController__


#include "cocos2d.h"
USING_NS_CC;

class Item;
class Chef;
class Pot;
class LevelProvider;
class UserDataProvider;
class ScoreLayer;
class Multiplier;
class GameCycleIndicator;
class Conveyor;
class MindCloudTips;
class BonusMenu;

class ControlPointDef : public cocos2d::Ref {
   
public:
   ControlPointDef(cocos2d::Point aControlPoint, int aControlPointType)
   {
      _controlPoint = Point(aControlPoint);
      _controlPointType = aControlPointType;
   };
   
   static ControlPointDef* create(cocos2d::Point aControlPoint, int aControlPointType)
   {
      return new ControlPointDef(aControlPoint, aControlPointType);
   }
   
   ~ControlPointDef(){};
   
   Point _controlPoint;
   int _controlPointType;
};


class GameController : public cocos2d::Ref {

public:

   GameController();

   ~GameController();

   static GameController* createWitLayer(cocos2d::Layer* aGameLayer);

   bool initWithLayer(cocos2d::Layer* aGameLayer);
   
   void startGame();
   
   void stopGame();
    void restartGame();
   
   void update(float dt);
    
    void changeItemPath(Item* anItem, float angle, Vec2 anImpulse);

protected:
    void releaseAll(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
    void setUpInit(bool isStart);
   
   void arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
   
   void populateGameObjects(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
   
   void putIdleItemOnConveyour(float dt, Item* anItem);
   
   void setItemIdle(float dt, Item* anItem);

   void runTossActionWithScale(Item* anItem, ControlPointDef* aPointDef, float aDuration, cocos2d::Point anImpulse);

   void tossItem(Item* anItem, Vec2 anImpulse);
   
   void runBumpAction(Item* anItem);
   
   float getScaleFactor(cocos2d::Point anEndPoint, int aControlPointType);
    
    void checkGameProgress(Item* anItem);

    ControlPointDef* findControlPointDefByAngle(Item* anItem, float angle, float xImpulse);
   
    void processBonusState(float dt);
    void useActiveBonus();
    void resetActiveBonus();
    // model
   cocos2d::Vector<cocos2d::Node*>* _items;
   cocos2d::Vector<ControlPointDef*>* _cntPoints;
   
   float _convY;
   float _convVelY;
   float _convLegth;
   float _putNextItemDt;
   float _itemTimer;

   cocos2d::Vec2 _itemIdlePos;
   int _idxRotated;
   
   Pot* _thePot;
   Chef* _theChef;
    
    LevelProvider* _levelInfo;
    UserDataProvider* _userData;
    ScoreLayer* _scoreLayer;
    Multiplier* _multiplier;
    GameCycleIndicator* _gameCycleInd;
    Conveyor* _conv;
    MindCloudTips* cloudTips;
    Sprite* bg;
    BonusMenu* _bonusMenu;
    
    std::vector<int> _caughtItemsIds;
    
    float _bonusTimer; // if _bonusTimer > 0, the game using active bonus from bonus menu;
    //float _roundTimer;
    
private:
   
   cocos2d::Layer* _gameLayer;

};
#endif /* defined(__BlindChef__GameController__) */
