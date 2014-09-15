
#include "Dish.h"

Dish::Dish(){}


Dish::~Dish() {}

Dish* Dish::create(std::string anImageFileName, std::vector<int> anIngridientIDsList)
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

bool Dish::init(std::string anImageFileName, std::vector<int> anIngridientIDsList)
{

    _imageFileName = anImageFileName;
    _ingridientIDs = anIngridientIDsList;
    
    return true;
}

std::string Dish::getImageName()
{
    return nullptr;
}

std::vector<int> Dish::getIngridientIDs()
{
    return _ingridientIDs;
}




