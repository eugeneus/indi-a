
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
class ItemsPool;
class DishFactory;
class Dish;
class PerformanceMetrics;
class Stickers;
class ControlPointDef;


class GameController : public cocos2d::Ref {

public:

   GameController();

   ~GameController();

   static GameController* createWitLayer(cocos2d::Layer* aGameLayer);

   bool initWithLayer(cocos2d::Layer* aGameLayer);
   
   void stopGame();
    void restartGame();
   
   void update(float dt);
    
    void changeItemPath(Item* anItem, float angle, Vec2 anImpulse);
    void swipeItem(Item* anItem, Vec2 aStartSwipePoint);
    
    float getActualRoundTime();

protected:
    
    void resetCompletedRound();
    
    void setupNewRound();
    void setUpInit(bool isStart);
   
    void createScene();
    void arrangeSceneForRect(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);
    void arrangeBackground(cocos2d::Vec2 anOrigin, cocos2d::Size aVisibleSize);

    
    void runItemConveyorAction(Item *anItem);
    void putItemOnConveyour(float dt);
   
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
    
    //void updatePerformanceMetrics();
    
    
    
    // model
    std::vector<Item*> _items;
    cocos2d::Vector<ControlPointDef*>* _cntPoints;
   
    cocos2d::Vector<Item*>  _requiredItems;
    cocos2d::Vector<Item*>  _foodItems;
    cocos2d::Vector<Item*>  _garbageItems;
    
   
    float _convY;
    float _convVelY;
    float _convLegth;
    float _putNextItemDt;
    float _maxReqiredItemInterval;
    
    float _elasedTest;
    
    float _requiredItemTimer;

    cocos2d::Vec2 _itemIdlePos;
    int _idxRotated;
   
    Pot* _thePot;
    Chef* _theChef;
    float _currGameTime;
    bool _isTimerBeforeEnd = false;
    bool _isTimerEnd = false;
    LevelProvider* _levelInfo;
    //UserDataProvider* _userData;
    Stickers *_stickers;
    ScoreLayer* _scoreLayer;
    Multiplier* _multiplier;
    GameCycleIndicator* _gameCycleInd;
    Conveyor* _conv;
    MindCloudTips* _cloudTips;
    Sprite* bg;
    BonusMenu* _bonusMenu;
    ItemsPool* _itemsPool;
    DishFactory* _dishFactory;
    std::vector<Dish *> _dishesQueue;
    Dish* _mainCource;
    int _levelCounter;
    
    PerformanceMetrics* _perfMetric;
    
    std::vector<int> _caughtItemsIds;
    
    float _bonusTimer; // if _bonusTimer > 0, the game using active bonus from bonus menu;
    
    bool _isControllerWaitingStop;
    
    cocos2d::Point _cloudTipsPos;
    
    // round/hard/waves support
    int _nRound;
    // default metrics
    int _maxBandVelosity;
    
    int _maxRepeatIngridients;
    
    int _maxRepeatBonus1;
    
    int _maxRepeatBonus2;
    
    int _maxRepeatBonus3;
    
    float _maxGarbagePct;
    
    // active mentics
    int _bandVelosity;
    
    int _repeatIngridients;
    
    int _repeatBonus1;
    
    int _repeatBonus2;
    
    int _repeatBonus3;
    
    float _garbagePct;
    
    float _densityFactor;
    
    
    
    
private:
   
   cocos2d::Layer* _gameLayer;

};
#endif /* defined(__BlindChef__GameController__) */
