
#include "DishFactory.h"
#include "Dish.h"

DishFactory::DishFactory(){}


DishFactory::~DishFactory() {}

DishFactory* DishFactory::create(const char* aFileName)
{
    DishFactory *pRet = new DishFactory();
    if (pRet && pRet->init(aFileName))
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

bool DishFactory::init(const char* aFileName)
{
    _dishesMap = cocos2d::FileUtils::getInstance()->getValueMapFromFile(aFileName);
    _nextLevel = 1;

    return true;
}

void DishFactory::getNextLevel(int aLevel)
{
    char levelStr[5] = {0};
    sprintf(levelStr, "%d", aLevel);
    _levelMap = _dishesMap.at(levelStr).asValueMap();
}

Dish* DishFactory::createDish(cocos2d::ValueMap aData)
{
    // create Dish from map
    cocos2d::Value fileNameVal= aData.at("ImageFileName");
    std::string fileName = fileNameVal.asString();
    cocos2d::ValueVector typesList = aData.at("ingridients").asValueVector();
    std::vector<int> ingridients;
    if (typesList.size() > 0) {
        for (int i = 0; i < typesList.size(); i++) {
            cocos2d::Value value = typesList.at(i);
            ingridients.push_back(value.asInt());
        }
    }
    
    Dish* newDish = Dish::create(fileName, ingridients);
    
    return newDish;


Dish* DishFactory::getRandomDish()
{
    if(_levelMap.size() == 0){
        this->getNextLevel(_nextLevel);
        if (_nextLevel < _dishesMap.size()) {
            _nextLevel++;
        }
        else{_nextLevel = 1;}
    }
    
    cocos2d::ValueMap::iterator rnd = _levelMap.begin();
    std::advance(rnd, rand() % _levelMap.size());
    if(rnd == _levelMap.end()){
        rnd = _levelMap.begin();
    }
    
   Dish* nextDish = this->createDish(rnd->second.asValueMap());
   _levelMap.erase(rnd);
    return nextDish;
}}