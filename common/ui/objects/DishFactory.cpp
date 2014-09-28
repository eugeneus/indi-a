
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
    
    return true;
}

Dish* DishFactory::getRandomDish()
{
    cocos2d::ValueMap::iterator rnd = _dishesMap.begin();
    std::advance(rnd, rand() % _dishesMap.size()); // TODO: set 2 for test only _dishesMap.size());
    if(rnd == _dishesMap.end()){
        rnd = _dishesMap.begin();
    }
    
    // create Dish from map
    cocos2d::ValueMap dish = rnd->second.asValueMap();
    cocos2d::Value fileNameVal= dish.at("ImageFileName");
    std::string fileName = fileNameVal.asString();
    cocos2d::ValueVector typesList = dish.at("ingridients").asValueVector();
    std::vector<int> ingridients;
    if (typesList.size() > 0) {
        for (int i = 0; i < typesList.size(); i++) {
            cocos2d::Value value = typesList.at(i);
            ingridients.push_back(value.asInt());
        }
    }

    Dish* newDish = Dish::create(fileName, ingridients);
    
    return newDish;
}