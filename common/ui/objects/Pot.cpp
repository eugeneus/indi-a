
#include "Pot.h"

USING_NS_CC;

Pot* Pot::create(cocos2d::Layer* aGameLayer, int aFrontZO, int aBackZO)
{
    Pot *pRet = new Pot();
    if (pRet && pRet->init(aGameLayer, aFrontZO, aBackZO))
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

bool Pot::init(cocos2d::Layer* aGameLayer, int aFrontZO, int aBackZO) {
    
    if(!LayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
 
    _front = Sprite::createWithSpriteFrameName("pot_front_1.png");
   aGameLayer->addChild(_front, aFrontZO);
    _front->setAnchorPoint(Vec2(0,0));
    
    _back = Sprite::createWithSpriteFrameName("pot_back_1.png");
   aGameLayer->addChild(_back, aBackZO);
   _back->setAnchorPoint(Vec2(0,0));
    
    this->setAnchorPoint(Vec2(0,0));
   this->setContentSize(_front->getContentSize());
   
    return true;
}

Sprite* Pot::getFront() {
    return _front;
}

Sprite* Pot::getBack() {
    return _back;
}

Rect Pot::getFrontRect()
{
   Point origin = Point(_front->getPosition());
   Size sz =   Size(_front->getContentSize() * _front->getScale()); //
   return Rect(origin.x,origin.y, sz.width, sz.height);
}

Rect Pot::getBackRect()
{
   Point origin = Point(_back->getPosition());
   Size sz =   Size(_back->getContentSize() * _back->getScale()); //
   return Rect(origin.x,origin.y, sz.width, sz.height);
}

void Pot::setOriginPos(Point anOrigin)
{
   _front->setPosition(anOrigin);
   _back->setPosition(anOrigin);
}
