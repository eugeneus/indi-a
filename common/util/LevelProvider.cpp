
#include "LevelProvider.h"

LevelProvider::LevelProvider()
{
    _levelId = 0;
    _requiredLaunchCount = -1;
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

std::string getStringValue(ValueMap map, const char* key) {
    Value value = map.at(key);
    return value.asString();
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

float getIntValue(ValueMap map, const char* key) {
    Value value = map.at(key);
    return value.asInt();
}


bool LevelProvider::initForLevel(int levelId)
{
    _levelId = levelId;
    if (_levelId > 0) {
    
        const char *levelFileName = CCString::createWithFormat("level_%i.plist", levelId)->getCString();
        _levelMap = FileUtils::getInstance()->getValueMapFromFile(levelFileName);
        
        _speed = getFloatValue(_levelMap, "speed");
        _roundTime = getFloatValue(_levelMap, "roundTime");
        _bg = getStringValue(_levelMap, "bg");
        _tipsBg = getStringValue(_levelMap, "tipsBg");
        
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

float LevelProvider::getRoundTime() {
    return _roundTime;
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

std::string LevelProvider::getTipsBgSpriteFrameName() {
    return _tipsBg;
}

std::map<int,int> LevelProvider::getBonusItems()
{
    if (_bonusItems.size() > 0)
        return _bonusItems;
    
    Value itemsValue = _levelMap.at("bonusItems");
    ValueVector items = itemsValue.asValueVector();
    int id;
    int val;
    if (items.size() > 0) {
        Value bonusVal;
        for (int i = 0; i < items.size(); i++) {
            bonusVal = items.at(i);
            id = bonusVal.asValueMap().at("itemId").asInt();
            val = bonusVal.asValueMap().at("appearsPerLevel").asInt();
            _bonusItems.insert(std::pair<int, int>(id, val));
        }
    }
    return _bonusItems;
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

bool isExistId(int reqId, std::vector<int> itemsIds) {
    for (int j = 0; j < itemsIds.size(); j++) {
        int itemId = itemsIds.at(j);
        if (itemId == reqId) {
            return true;
        }
    }
    
    return false;
}

bool LevelProvider::checkAllRequiredExist(std::vector<int> itemsIds) {
    if (itemsIds.size() >= _requiredItems.size()) {
        for (int i = 0; i < _requiredItems.size(); i++) {
            int reqId = _requiredItems.at(i);
            bool isExist = isExistId(reqId, itemsIds);
            
            if (!isExist) {
                return false;
            }
        }
        
        return true;
    }
    
    return false;
}

int LevelProvider::getLevelId() {
    return _levelId;
}

std::string LevelProvider::getBgSpriteFrameName() {
    return _bg;
}

int LevelProvider::getRequiredAppearsPerLevel()
{
    if(_requiredLaunchCount < 0){ //lazy init
        //Value itemsVlaue = ;
        //ValueMap itemsMap = itemsVlaue.asValueMap();
        _requiredLaunchCount = getIntValue(_levelMap.at("items").asValueMap(), "requiredAppearsPerLevel");
    }
    return _requiredLaunchCount;
}
