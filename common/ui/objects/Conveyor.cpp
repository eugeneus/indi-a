
#include "Conveyor.h"

USING_NS_CC;

Conveyor* Conveyor::create(float aSpeed, float aLength)
{
    Conveyor *pRet = new Conveyor();
    if (pRet && pRet->init(aSpeed, aLength))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Conveyor::init(float aSpeed, float aLength) {
    
    if(!super::init("conveyer_1.png", aSpeed, aLength)) {
        return false;
    }
    
    
    return true;
}

float Conveyor::getFirstItemPosY() {
    Vector<Node*> children = super::getChildrenItems();
    Node* firstItem = children.front();
    
    return firstItem->getPosition().y;
}