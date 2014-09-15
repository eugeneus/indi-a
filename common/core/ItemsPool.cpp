
#include "ItemsPool.h"
#include "Item.h"
#include "LevelProvider.h"
#include "ItemFactory.h"
#include "Dish.h"


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
_arbitraryItemInterval(0.0f)
{}

ItemsPool::~ItemsPool() {}

ItemsPool* ItemsPool::create(LevelProvider* aLevelInfo, Dish* aDish)
{
    
    ItemsPool *pRet = new ItemsPool();
    
    pRet->_maxRequiredItemsCounter = aLevelInfo->getRequiredAppearsPerLevel();
    pRet->_requiredItemsInterval =  (aLevelInfo->getRoundTime() - pRet->_elapsedRoundTime) / pRet->_maxRequiredItemsCounter;
    pRet->_requiredItemsInterval =  pRet->_requiredItemsInterval/3.0f;
    
    std::vector<int> ingridients = aDish->getIngridientIDs();
    for (int i = 0; i < ingridients.size(); i++){
        pRet->_requiredItemsCounter.insert(std::pair<int,int>(ingridients.at(i), pRet->_maxRequiredItemsCounter));
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
    
    _elapsedRoundTime += dt;
    _requiredItemsInterval -= dt;
    _bonusItemsInterval -= dt;
    _arbitraryItemInterval -= dt;
    
    // one of level complication technique:
    // for harder level start pulling required item closer to a round end.
    // i.e. inital value of _requiredItemsInterval should be multipied by complication factor
    // try to find required Item (dish ingridients)
    if (_maxRequiredItemsCounter > 0 && _requiredItemsInterval < 0.0f) {
        cycleTerminator = 3;
        std::map<int,int>::iterator it = _requiredItemsCounter.begin();
        
        int currentCount = _maxRequiredItemsCounter;
        while (suitableItemId < 0 && cycleTerminator > 0) {
            if (it == _requiredItemsCounter.end()) {
                cycleTerminator--;
                currentCount--;
                it = _requiredItemsCounter.begin();
            }
            else if (it->second == currentCount){
                suitableItemId = it->first;
                it->second -= 1;
                suitableItemType = 0;
            }
            else{
                ++it;
            }
        }
        
        _requiredItemsInterval = ((anEffectiveRoundTime - this->_elapsedRoundTime) / (currentCount + 2)) - 0.2f;
        
    }

    // try to find Bonus item
    if (this->getBonusHasMaxCount() > 0 && suitableItemId < 0 && _bonusItemsInterval < 0) {
        cycleTerminator = 2;
        std::map<int,int>::iterator rnd = _bonusItemsCounter.begin();
        std::advance(rnd, rand() % _bonusItemsCounter.size());
        
        while (suitableItemId < 0 && cycleTerminator > 0) {
            if (rnd == _bonusItemsCounter.end()) {
                cycleTerminator--;
                rnd = _bonusItemsCounter.begin();
            }
            else if (rnd->second > 0){
                suitableItemId = rnd->first;
                rnd->second -= 1;
                suitableItemType = 0;
            }
            else{
                ++rnd;
            }
        }
        
        _bonusItemsInterval = (anEffectiveRoundTime -  this->_elapsedRoundTime) / this->getCurrenTotalBonuses();
    }

    if(suitableItemId < 0 && _arbitraryItemInterval < 0.0f){
        
        int rndFood = 0;
        int rndGarg = 0;
        int rnd = rand()%2;
        if (rnd) {
            rndGarg = 1;
        }
        else{
            rndFood = 1;
        }
        
        float pct = ((float)(_pulledFoodCount + rndFood))/((float)(_pulledFoodCount + rndFood + _pulledGarbageCount + rndGarg));
        
        if(_garbagePerFood > pct){
            rnd = 0;
        }
        
        if (!rnd) {
            cycleTerminator = 2;
            std::map<int,int>::iterator rnd = _foodItemsCounter.begin();
            std::advance(rnd, rand() % _foodItemsCounter.size());
            startID = rnd->first;
            
            while (suitableItemId < 0 && cycleTerminator > 0) {
                if(rnd == _foodItemsCounter.end()){
                    cycleTerminator--;
                    rnd = _foodItemsCounter.begin();
                }else if (rnd->second < 3) {
                    suitableItemId = rnd->first;
                    suitableItemType = 0;
                    rnd->second += 1;
                    _pulledFoodCount += 1;
                }
                else{
                    ++rnd;
                }
            }
            
            if (suitableItemId < 0) {
                suitableItemId = startID;
                suitableItemType = 0;
                _pulledFoodCount += 1;
            }
        }
        else{
            cycleTerminator = 2;
            std::map<int,int>::iterator rnd = _garbageItemsCounter.begin();
            std::advance(rnd, rand() % _garbageItemsCounter.size());
            startID = rnd->first;
            
            while (suitableItemId < 0 && cycleTerminator > 0) {
                if(rnd == _garbageItemsCounter.end()){
                    cycleTerminator--;
                    rnd = _garbageItemsCounter.begin();
                }else if (rnd->second < 3) {
                    suitableItemId = rnd->first;
                    suitableItemType = 1;
                    rnd->second += 1;
                    _pulledGarbageCount += 1;
                }
                else{
                    ++rnd;
                }
            }
            
            if (suitableItemId < 0) {
                suitableItemId = startID;
                suitableItemType = 1;
                _pulledGarbageCount += 1;
            }
        }
        
        _arbitraryItemInterval = 1.5f;
    }

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
    
    return maxCount;
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

