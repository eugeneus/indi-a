
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

   static ItemsPool* create(LevelProvider* aLevelInfo, Dish* aDish);

    Item* getItemFromPool(std::vector<Item*>* anItemList,
                          float dt,
                          float anEffectiveRoundTime,
                          cocos2d::Vec2 aStartPos,
                          int aStartZOrder);

protected:
    
    Item* getItemByType(std::vector<Item*>* anItemList,
                        int anItemID,
                        int anItemType,
                        cocos2d::Vec2 aStartPos,
                        int aStartZOrder);
    
    int getCurrenTotalBonuses();
    
    int getBonusHasMaxCount();
    
    void decreaseBonusCount(int aBonusItemId);

    std::map<int,int> _requiredItemsCounter;
    int _maxRequiredItemsCounter;
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
   
private:


};
#endif /* defined(__BlindChef__ItemsPool__) */
