
#ifndef __BlindChef__ItemsPool__
#define __BlindChef__ItemsPool__

#include "cocos2d.h"

class Item;
class Dish;
class LevelProvider;

class ItemsPool {

public:

   ItemsPool();

   ~ItemsPool();

   
    static ItemsPool* create(LevelProvider* aLevelInfo,
                             float aMaxGarbagePct,
                             int aMaxRepeatIngridients,
                             int aMaxRepeatBonus1,
                             int aMaxRepeatBonus2,
                             int aMaxRepeatBonus3
                             );
    
    void setConveyorLength(float aConveyorLength);

    Item* getItemFromPool(std::vector<Item*>* anItemList,
                          float dt,
                          float anEffectiveRoundTime,
                          int aStartZOrder,
                          float aBandVelosity);
    
    void updateRequredItems(Dish* aDish);
    
    void resetForNewRound(int aRoundNumber, cocos2d::Vec2 aStartPos, Dish* aDish);
    
protected:
    
    Item* getItemByType(std::vector<Item*>* anItemList,
                        int anItemID,
                        int anItemType,
                        int aStartZOrder);
    
    int getCurrenTotalBonuses();
    
    int getBonusHasMaxCount();
    
    void decreaseBonusCount(int aBonusItemId);

    std::map<int,int> _requiredItemsCounter;
    //int _maxRequiredItemsCounter;
    float _requiredItemsInterval; // time interval to launch next required item
    
    std::map<int,int> _bonusItemsCounter;
    int _maxBonusItemsCounter;
    float _bonusItemsInterval; // time interval to launch next bonus item

    std::map<int,int> _foodItemsCounter;

    std::map<int,int> _garbageItemsCounter;
    
    float _arbitraryItemInterval; // time interval to launch next good/garbage item
    float _elapsedRoundTime;
    int _pulledGarbageCount;
    int _pulledFoodCount;
    float _garbagePerFood;
    float _minItemInterval;
    
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
    
    int _nRound;
    
    cocos2d::Point _startItemPos;
    
    
    Item* _recentPulledItem;
    
    float _convLength;
    float _pointsInterval;
    
   
private:


};
#endif /* defined(__BlindChef__ItemsPool__) */
