
#include "Hand.h"

USING_NS_CC;

Hand* Hand::create()
{
    Hand *pRet = new Hand();
    if (pRet && pRet->init())
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

bool Hand::init() {
    
    if(!super::init()) {
        return false;
    }
    
    handImg = Sprite::createWithSpriteFrameName("hand_left_1.png");
    this->setContentSize(handImg->getContentSize());
    this->setScale(0.7f);
    this->addChild(handImg, 0);
    
    
    return true;
}

void Hand::mirrorImg() {
    handImg->setFlippedX(true);
}