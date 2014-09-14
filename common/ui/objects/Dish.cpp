
#include "Dish.h"

Dish::Dish(){}


Dish::~Dish() {}

Dish* create(std::string anImageFileName, std::vector<int> anIngridientIDsList)
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

bool init(std::string anImageFileName, std::vector<int> anIngridientIDsList)
{

    return true;
    
}



