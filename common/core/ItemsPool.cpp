
#include "ItemsPool.h"
#include "Item.h"
#include "LevelProvider.h"

ItemsPool::ItemsPool():
_requiredItemsInterval(0.0f),
_bonusItemsInterval(0.0f),
_foodItemsInterval(0.0f),
_garbageItemsInterval(0.0f)
{}


ItemsPool::~ItemsPool() {}

ItemsPool* ItemsPool::create(LevelProvider* aLevelInfo){
    
    ItemsPool *pRet = new ItemsPool();
    
    int appears = aLevelInfo->getRequiredAppearsPerLevel();
    std::vector<int> itemTypes = aLevelInfo->getRequiredItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_requiredItemsCounter.insert(std::pair<char,int>(itemTypes.at(i),appears));
    }
    
    itemTypes = aLevelInfo->getAllowedFoodItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_foodItemsCounter.insert(std::pair<char,int>(itemTypes.at(i),0));
    }
    
    
    itemTypes = aLevelInfo->getAllowedGarbageItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_garbageItemsCounter.insert(std::pair<char,int>(itemTypes.at(i),0));
    }
    
    pRet->_bonusItemsCounter = aLevelInfo->getBonusItems();

   return pRet;
}

Item* getItemFromPool(cocos2d::Vector<Item*>* anItemList, float dt)
{
    return nullptr;
}

