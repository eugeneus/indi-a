
#ifndef __BlindChef__ItemsPool__
#define __BlindChef__ItemsPool__

#include "cocos2d.h"

class Item;
class LevelProvider;

class ItemsPool {

public:

   ItemsPool();

   ~ItemsPool();

   static ItemsPool* create(LevelProvider* aLevelInfo);

    Item* getItemFromPool(std::vector<Item*>* anItemList, float dt, float anEffectiveRoundTime);

protected:
    
    int getCurrenTotalBonuses();
    
    int getBonusHasMaxCount();
    
    int getBonusHasFirstBiggerCount();
    
    void decreaseBonusCount(int aBonusItemId);

    //cocos2d::Vector<Item*> _items; // contains overall list of items
    //cocos2d::Map<std::string, ItemList*> _requiredPool;
    
    //std::queue<Item*> _requiredItem;
    
    std::map<int,int> _requiredItemsCounter;
    int _maxRequiredItemsCounter;
    float _requiredItemsInterval; // time interval to launch next required item
    
    std::map<int,int> _bonusItemsCounter;
    int _maxBonusItemsCounter;
    float _bonusItemsInterval; // time interval to launch next bonus item

    std::map<int,int> _foodItemsCounter;
    //float _foodItemsInterval; // time interval to launch next bonus item

    std::map<int,int> _garbageItemsCounter;
    //float _garbageItemsInterval; // time interval to launch next bonus item
    
    float _arbitraryItemInterval; // time interval to launch next good/garbage item
    float _elapsedRoundTime;
    int _pulledGarbageCount;
    int _pulledFoodCount;
    float _garbagePerFood;
    int _recentFoodID;
    int _recentGarbageID;
    
    
   
private:


};
#endif /* defined(__BlindChef__ItemsPool__) */
