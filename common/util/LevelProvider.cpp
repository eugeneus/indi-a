
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


float getFloatValue(ValueMap map, const char* key) {
    Value value = map.at(key);
    return value.asFloat();
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

bool LevelProvider::initForLevel(int levelId)
{
    _levelId = levelId;
    if (_levelId > 0) {
    
        const char *levelFileName = CCString::createWithFormat("level_%i.plist", levelId)->getCString();
        _levelMap = FileUtils::getInstance()->getValueMapFromFile(levelFileName);
        
        _speed = getFloatValue(_levelMap, "speed");
        _time = getFloatValue(_levelMap, "time");
        
        _allowedFoodItems = getAllowedItems(_levelMap, "allowedFoodItems");
        _allowedGarbageItems = getAllowedItems(_levelMap, "allowedGarbageItems");
        _requiredItems = getAllowedItems(_levelMap, "requiredFoodItems");
        
        return true;
    }
    
    return false;
}

float LevelProvider::getSpeed() {
    return _speed;
}

float LevelProvider::getTime() {
    return _time;
}

std::vector<int> LevelProvider::getAllowedFoodItems() {

    return _allowedFoodItems;
}

std::vector<int> LevelProvider::getAllowedGarbageItems() {
    
    return _allowedGarbageItems;
}

std::vector<int> LevelProvider::getRequiredItems() {
    
    return _requiredItems;
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
