
#include "Hands.h"

USING_NS_CC;

Hands* Hands::create(float dist)
{
    Hands *pRet = new Hands();
    if (pRet && pRet->init(dist))
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

bool Hands::init(float dist) {
    
    if(!super::init()) {
        return false;
    }
/*
    leftHand = Hand::create();
    leftHand->setPosition(Vec2(leftHand->getPosition().x + dist - 60, leftHand->getPosition().y + 100));
    this->addChild(leftHand, 2);
    
    rightHand = Hand::create();
    rightHand->mirrorImg();
    rightHand->setPosition(Vec2(rightHand->getPosition().x + 25, rightHand->getPosition().y + 100));
    this->addChild(rightHand, 2);
*/    
    
    return true;
}