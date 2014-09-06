
#include "ItemsPool.h"
#include "Item.h"
#include "LevelProvider.h"

ItemsPool::ItemsPool():
_requiredItemsInterval(0.0f),
_bonusItemsInterval(0.0f),
//_foodItemsInterval(0.0f),
//_garbageItemsInterval(0.0f),
_elapsedRoundTime(0.0f),
_maxBonusItemsCounter(0),
_pulledGarbageCount(0),
_pulledFoodCount(0),
_garbagePerFood(0.3f),
_recentFoodID(-1),
_recentGarbageID(-1)
{}


ItemsPool::~ItemsPool() {}

ItemsPool* ItemsPool::create(LevelProvider* aLevelInfo){
    
    ItemsPool *pRet = new ItemsPool();
    
    pRet->_maxRequiredItemsCounter = aLevelInfo->getRequiredAppearsPerLevel();
    pRet->_requiredItemsInterval =  (aLevelInfo->getRoundTime() - pRet->_elapsedRoundTime) / pRet->_maxRequiredItemsCounter;
    
    std::vector<int> itemTypes = aLevelInfo->getRequiredItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_requiredItemsCounter.insert(std::pair<int,int>(itemTypes.at(i), pRet->_maxRequiredItemsCounter));
    }
    
    itemTypes = aLevelInfo->getAllowedFoodItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_foodItemsCounter.insert(std::pair<int,int>(itemTypes.at(i),0));
    }
    
    
    itemTypes = aLevelInfo->getAllowedGarbageItems();
    for (int i = 0; i < itemTypes.size(); i++){
        pRet->_garbageItemsCounter.insert(std::pair<int,int>(itemTypes.at(i),0));
    }
    
    pRet->_bonusItemsCounter = aLevelInfo->getBonusItems();
    pRet->_bonusItemsInterval = (aLevelInfo->getRoundTime() - pRet->_elapsedRoundTime) / pRet->getCurrenTotalBonuses();
    
   return pRet;
}

Item* ItemsPool::getItemFromPool(std::vector<Item*>* anItemList, float dt, float anEffectiveRoundTime)
{
    Item* suitableItem = nullptr;
    int suitableItemId = -1;
    int cycleTerminator = 3;
    
    _elapsedRoundTime += dt;
    _requiredItemsInterval -= dt;
    _bonusItemsInterval -= dt;
    _arbitraryItemInterval -= dt;
    
    // one of level complication technique:
    // for harder level start pulling required item closer to a round end.
    // i.e. inital value of _requiredItemsInterval should be multipied by complication factor
    
    // try to find required Item (dish ingridients)
    if (_maxRequiredItemsCounter > 0 && _requiredItemsInterval < 0.0f) {
        
        std::map<int,int>::iterator it = _requiredItemsCounter.begin();
        
        while (suitableItem < 0 && cycleTerminator < 0) {
            if (it->second == this->_maxRequiredItemsCounter) {
                suitableItemId = it->first;
            }
            else if(it != _requiredItemsCounter.end()){
                ++it;
            }
            else{
                _maxRequiredItemsCounter--;
                cycleTerminator--;
                it = _requiredItemsCounter.begin();
            }
        }
        
        _requiredItemsInterval = (anEffectiveRoundTime - this->_elapsedRoundTime) / this->_maxRequiredItemsCounter;
    }
    
    // try to find Bonus item
    if (suitableItemId < 0) {
        std::map<int,int>::iterator it = _bonusItemsCounter.begin();
        
        while (suitableItem < 0 && cycleTerminator < 0) {
            if (it->second == this->_maxRequiredItemsCounter) {
                suitableItemId = it->first;
            }
            else if(it != _bonusItemsCounter.end()){
                ++it;
            }
            else{
                cycleTerminator--;
                it = _bonusItemsCounter.begin();
            }
        }
        
        _bonusItemsInterval = (anEffectiveRoundTime -  this->_elapsedRoundTime) / this->getCurrenTotalBonuses();

    }
    
    if(suitableItemId < 0 && _arbitraryItemInterval < 0.0f){
        
        if(_garbagePerFood > _pulledGarbageCount/(_pulledFoodCount+0.01f)){
            // try to get arbitrary food item
            _pulledFoodCount += 1.0f;
            std::map<int,int>::iterator it;
            if(_recentFoodID < 0){
                it = _foodItemsCounter.begin();
            }
            else{
                it = _foodItemsCounter.find(_recentFoodID);
            }
            int prevCounter = it->second;
            
            while (suitableItem < 0 && cycleTerminator < 0) {
                if (it->second >= prevCounter) {
                    suitableItemId = it->first;
                }
                else if(it != _foodItemsCounter.end()){
                    ++it;
                }
                else{
                    cycleTerminator--;
                    it = _foodItemsCounter.begin();
                }
            }
        }
        else{
            // try to get garbage item
            _pulledGarbageCount += 1.0f;
            std::map<int,int>::iterator it;
            if(_recentGarbageID < 0){
                it = _garbageItemsCounter.begin();
            }
            else{
                it = _garbageItemsCounter.find(_recentGarbageID);
            }
            int prevCounter = it->second;
            
            while (suitableItem < 0 && cycleTerminator < 0) {
                if (it->second >= prevCounter) {
                    suitableItemId = it->first;
                }
                else if(it != _garbageItemsCounter.end()){
                    ++it;
                }
                else{
                    cycleTerminator--;
                    it = _garbageItemsCounter.begin();
                }
            }
        }
        
        _arbitraryItemInterval = 0.3f;
    
    }
    
    // final step:
    // try to find anItem by suitableID in main array
    // if not found  - create it
//    std::vector<Item*>::iterator it;
//    if(std::find(anItemList->begin(), anItemList->end(), it)!= anItemList->end()){
//        // Find the item
//    }
    return suitableItem;
}

int ItemsPool::getCurrenTotalBonuses()
{
    int total = 0;
    for(auto bonus : _bonusItemsCounter){
        total += bonus.second;
    }
    return total;
}

int ItemsPool::getBonusHasMaxCount()
{
    int maxCount = 0;
    for (auto bonus : _bonusItemsCounter) {
        if (maxCount > bonus.second) {
            maxCount = bonus.second;
        }
    }
}

int ItemsPool::getBonusHasFirstBiggerCount()
{
    int maxCount = 0;
    std::map<int,int>::iterator it = _bonusItemsCounter.begin();
    while (it != _bonusItemsCounter.end() && maxCount <= it->second) {
        it++;
    }
}

void ItemsPool::decreaseBonusCount(int aBonusItemId)
{
    std::map<int,int>::iterator it = _bonusItemsCounter.find(aBonusItemId);
    if (it->first == aBonusItemId) {
        if(it->second > 0){
            it->second--;
        }
    }
}

