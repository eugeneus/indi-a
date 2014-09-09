
#include "ItemsPool.h"
#include "Item.h"
#include "LevelProvider.h"
#include "ItemFactory.h"

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
_recentGarbageID(-1),
_arbitraryItemInterval(0.0f)
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
    
    std::vector<int> itemTypes1 = aLevelInfo->getAllowedFoodItems();
    for (int i = 0; i < itemTypes1.size(); i++){
        pRet->_foodItemsCounter.insert(std::pair<int,int>(itemTypes1.at(i),0));
    }
    
    
    std::vector<int> itemTypes2 = aLevelInfo->getAllowedGarbageItems();
    for (int i = 0; i < itemTypes2.size(); i++){
        pRet->_garbageItemsCounter.insert(std::pair<int,int>(itemTypes2.at(i),0));
    }
    
    pRet->_bonusItemsCounter = aLevelInfo->getBonusItems();
    pRet->_bonusItemsInterval = (aLevelInfo->getRoundTime() - pRet->_elapsedRoundTime) / pRet->getCurrenTotalBonuses();
    
   return pRet;
}

Item* ItemsPool::getItemByType(std::vector<Item*>* anItemList,
                               int anItemID,
                               int anItemType,
                               cocos2d::Vec2 aStartPos,
                               int aStartZOrder)
{
    Item* suitableItem  = nullptr;
    if(anItemID < 0 && anItemType < 0)
        return suitableItem;

    std::vector<Item*>::iterator iItem = anItemList->begin();
        
    Item* nextItem = nullptr;
        
    while (!suitableItem && iItem != anItemList->end()) {
        nextItem = (Item*)*iItem;
        if (nextItem->_itemType == anItemType &&
            nextItem->_itemId == anItemID &&
            nextItem->getPosition().x == aStartPos.x &&
            nextItem->getLocalZOrder() == aStartZOrder) {
            suitableItem = nextItem;
        }
        ++iItem;
    }
        
        if (!suitableItem) {
            suitableItem = ItemFactory::createItem(anItemType, anItemID);
            suitableItem->setPosition(aStartPos);
            suitableItem->setLocalZOrder(aStartZOrder);
            anItemList->push_back(suitableItem);
        }
    
    return suitableItem;
}

Item* ItemsPool::getItemFromPool(std::vector<Item*>* anItemList,
                                 float dt,
                                 float anEffectiveRoundTime,
                                 cocos2d::Vec2 aStartPos,
                                 int aStartZOrder)

{
    Item* suitableItem = nullptr;
    int suitableItemId = -1;
    int suitableItemType = -1;
    int cycleTerminator = 3;
    
    int startID = -1;
    int startQ = -1;
    
    _elapsedRoundTime += dt;
    _requiredItemsInterval -= dt;
    _bonusItemsInterval -= dt;
    _arbitraryItemInterval -= dt;
    
    
    
    // one of level complication technique:
    // for harder level start pulling required item closer to a round end.
    // i.e. inital value of _requiredItemsInterval should be multipied by complication factor
    

    // try to find required Item (dish ingridients)
/*
    if (_maxRequiredItemsCounter > 0 && _requiredItemsInterval < 0.0f) {
        
        std::map<int,int>::iterator it = _requiredItemsCounter.begin();
        
        while (suitableItemId < 0 && cycleTerminator > 0) {
            if (it->second == this->_maxRequiredItemsCounter) {
                suitableItemId = it->first;
                suitableItemType = 0;
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
        
        while (suitableItemId < 0 && cycleTerminator > 0) {
            if (it->second == this->_maxRequiredItemsCounter) { // should compare bonuses metrics, not required!
                suitableItemId = it->first;
                suitableItemType = 0;
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
*/
    
    if(suitableItemId < 0 && _arbitraryItemInterval < 0.0f){
        
        std::map<int,int>::iterator rnd = _foodItemsCounter.begin();
        std::advance(rnd, rand() % _foodItemsCounter.size());
        startID = rnd->first;
        startQ = rnd->second;

        while (suitableItemId < 0 && cycleTerminator > 0) {
            if(rnd == _foodItemsCounter.end()){
                cycleTerminator--;
                rnd = _foodItemsCounter.begin();
                //_recentFoodID = rnd->first;
                startQ += 1;
            }else if (rnd->second < startQ || rnd->second <= 0) {
                suitableItemId = rnd->first;
                //_recentFoodID = suitableItemId;
                suitableItemType = 0;
                startQ = rnd->second;
                rnd->second += 1;
                _pulledFoodCount += 1;
            }
            else{
                ++rnd;
            }
        }
        
        if (suitableItemId < 0) {
            suitableItemId = startID;
            //_recentFoodID = startID;
            suitableItemType = 0;
            _pulledFoodCount += 1;
        }
        //CCLOG("_arbitraryItemInterval = %d", suitableItemId);
        _arbitraryItemInterval = 0.8f;
    }
    
    
//        if(_garbagePerFood > ((float)(_pulledGarbageCount + 1))/((float)(_pulledFoodCount+0.01f))){
//            // try to get arbitrary food item
//            std::map<int,int>::iterator it;
//            if(_recentFoodID < 0){
//                it = _foodItemsCounter.begin();
//            }
//            else{
//                it = _foodItemsCounter.find(_recentFoodID);
//            }
//
//            int prevCounter = it->second;
//            while (suitableItemId < 0 && cycleTerminator > 0) {
//                if (it->second > prevCounter || it->second <= 0) {
//                    suitableItemId = it->first;
//                    _recentFoodID = suitableItemId;
//                    suitableItemType = 0;
//                    prevCounter = it->second;
//                    it->second += 1;
//                    _pulledFoodCount += 1;
//                }
//                else if(it != _foodItemsCounter.end()){
//                    ++it;
//                }
//                else{
//                    cycleTerminator--;
//                    it = _foodItemsCounter.begin();
//                    prevCounter += 1;
//                }
//            }
//        }
//        else{
//            // try to get garbage item
//            std::map<int,int>::iterator it;
//            if(_recentGarbageID < 0){
//                it = _garbageItemsCounter.begin();
//            }
//            else{
//                it = _garbageItemsCounter.find(_recentGarbageID);
//            }
//            int prevCounter = it->second;
//            
//            while (suitableItemId < 0 && cycleTerminator > 0) {
//                if (it->second > prevCounter || it->second <= 0) {
//                    suitableItemId = it->first;
//                    _recentGarbageID = suitableItemId;
//                    suitableItemType = 1;
//                    prevCounter = it->second;
//                    it->second += 1;
//                    _pulledGarbageCount += 1;
//                }
//                else if(it != _garbageItemsCounter.end()){
//                    ++it;
//                }
//                else{
//                    prevCounter += 1;
//                    cycleTerminator--;
//                    it = _garbageItemsCounter.begin();
//                }
//            }
//        }
        
    
    // final step:
    // try to find anItem by suitableID in main array
    // if not found  - create it

    if (suitableItemType >= 0 && suitableItemId >= 0)  { // there is no item (time is not reached)
        std::vector<Item*>::iterator iItem = anItemList->begin();
        
        Item* nextItem = nullptr;
        
        while (!suitableItem && iItem != anItemList->end()) {
            nextItem = (Item*)*iItem;
            if (nextItem->_itemType == suitableItemType &&
                nextItem->_itemId == suitableItemId &&
                nextItem->getPosition().x == aStartPos.x &&
                nextItem->getLocalZOrder() == aStartZOrder) {
                suitableItem = nextItem;
            }
            ++iItem;
        }
        
        if (!suitableItem) {
            suitableItem = ItemFactory::createItem(suitableItemType, suitableItemId);
            suitableItem->setPosition(aStartPos);
            suitableItem->setLocalZOrder(aStartZOrder);
            anItemList->push_back(suitableItem);
        }
    }
    
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

