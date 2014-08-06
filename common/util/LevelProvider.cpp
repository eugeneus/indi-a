
#include "LevelProvider.h"

LevelProvider::LevelProvider()
{
    _levelId = 0;
}

LevelProvider::~LevelProvider() {}

LevelProvider* LevelProvider::createForLevel(int levelId)
{
    
    LevelProvider *pRet = new LevelProvider();
    if (pRet && pRet->initForLevel(levelId))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool LevelProvider::initForLevel(int levelId)
{
    _levelId = levelId;
    if (_levelId > 0) {
    
        const char *levelFileName = CCString::createWithFormat("level_%i.plist", levelId)->getCString();
        _levelMap = FileUtils::getInstance()->getValueMapFromFile(levelFileName);
        
        
        _allowedFoodItems = getAllowedFoodItems();
        _allowedGarbageItems = getAllowedGarbageItems();
        _requiredItems = getRequiredItems();
        
        return true;
    }
    
    return false;
}

float LevelProvider::getSpeed() {
    Value speed = _levelMap.at("speed");
    return speed.asFloat();
}

std::vector<int> getAllowedItems(ValueMap map, const char* key) {
    std::vector<int> result;
    
    Value itemsVlaue = map.at("items");
    ValueMap itemsMap = itemsVlaue.asValueMap();
    Value currItemsValue = itemsMap.at(key);
    ValueVector currItemsVector = currItemsValue.asValueVector();
    if (currItemsVector.size() > 0) {
        for (int i = 0; i < currItemsVector.size(); i++) {
            Value value = currItemsVector.at(i);
            
            result.push_back(value.asInt());
        }
    }
    
    return result;
}

std::vector<int> LevelProvider::getAllowedFoodItems() {

    return getAllowedItems(_levelMap, "allowedFoodItems");
}

std::vector<int> LevelProvider::getAllowedGarbageItems() {
    
    return getAllowedItems(_levelMap, "allowedGarbageItems");
}

std::vector<int> LevelProvider::getRequiredItems() {
    
    return getAllowedItems(_levelMap, "requiredFoodItems");
}

bool LevelProvider::isRequiredItem(int itemId) {
    if (itemId > -1 ) {
        for (int i = 0; i < _requiredItems.size(); i++) {
            int reqId = _requiredItems.at(i);
            if (reqId == itemId) {
                return true;
            }
        }
    }
    
    return false;
}
