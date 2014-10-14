
#include "Dish.h"

Dish::Dish(){}


Dish::~Dish() {}

Dish* Dish::create(const std::string& anImageFileName, const std::vector<int>& anIngridientIDsList)
{
    Dish *pRet = new Dish();
    if (pRet && pRet->init(anImageFileName, anIngridientIDsList))
    {
        //pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }

}

bool Dish::init(const std::string& anImageFileName, const std::vector<int>& anIngridientIDsList)
{

    _imageFileName = anImageFileName;
    _ingridientIDs = anIngridientIDsList;
    
    return true;
}

std::string Dish::getImageName()
{
    return _imageFileName;
}

std::vector<int> Dish::getIngridientIDs()
{
    return _ingridientIDs;
}

bool Dish::checkAllRequiredExist(std::vector<int> itemsIds) {

    bool isOk = true;
    for (int nid : _ingridientIDs) {
        if (std::find(itemsIds.begin(), itemsIds.end(), nid) == itemsIds.end()) {
            isOk = false;
        }
    }
    return isOk;
}



bool Dish::isRequiredItem(int anItemId) {
    
    return (std::find(_ingridientIDs.begin(), _ingridientIDs.end(), anItemId) != _ingridientIDs.end());
}




