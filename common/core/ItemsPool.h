
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

    Item* getItemFromPool(cocos2d::Vector<Item*>* anItemList, float dt);

protected:

    //cocos2d::Vector<Item*> _items; // contains overall list of items
    //cocos2d::Map<std::string, ItemList*> _requiredPool;
    
    //std::queue<Item*> _requiredItem;
    
    std::map<int,int> _requiredItemsCounter;
    float _requiredItemsInterval; // time interval to launch next required item
    
    std::map<int,int> _bonusItemsCounter;
    float _bonusItemsInterval; // time interval to launch next bonus item

    std::map<int,int> _foodItemsCounter;
    float _foodItemsInterval; // time interval to launch next bonus item

    std::map<int,int> _garbageItemsCounter;
    float _garbageItemsInterval; // time interval to launch next bonus item
   
private:


};
#endif /* defined(__BlindChef__ItemsPool__) */
