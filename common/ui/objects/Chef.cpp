
#include "Chef.h"

USING_NS_CC;

Chef::Chef(){}
Chef::~Chef(){}

Chef* Chef::create(cocos2d::Layer* aLayer)
{
    Chef *pRet = new Chef();
    if (pRet && pRet->init(aLayer))
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

bool Chef::init(cocos2d::Layer* aLayer) {
   
//"chef_1.png", "chef_%i.png", 4, 0.9
   
   Size visibleSize = Director::getInstance()->getVisibleSize();
   this->_layer = aLayer;
   
   _chef = Sprite::createWithSpriteFrameName("chef_1.png");
   _chef->setAnchorPoint(Point(0,0));
   aLayer->addChild(_chef,1);
   
   // just temporary scale
   float scaleFactor = 0.5f;
   _chef->setScale(scaleFactor);
   Size chefSize = _chef->getContentSize();
   Point chefOrigin = Point((visibleSize.width - (chefSize.width*scaleFactor))/2.0f, 0.0f);
   _chef->setPosition(chefOrigin);
   _chefRect = Rect(chefOrigin.x,chefOrigin.y,chefSize.width*scaleFactor,chefSize.height*scaleFactor);
   
   float HscaleFactor = 0.7f;
   
   _rightHand = Sprite::createWithSpriteFrameName("hand_left_1.png");
   aLayer->addChild(_rightHand,1);
   _rightHand->setAnchorPoint(Point(0,0));
   _rightHand->setScale(HscaleFactor);
   _rightHand->setFlippedX(true);

   Size handSize = _rightHand->getContentSize();
   handSize.width = handSize.width*HscaleFactor;
   handSize.height = handSize.height*HscaleFactor;
   _rightHandRect = Rect(chefOrigin.x,chefOrigin.y,handSize.width,handSize.height);
   _rightHand->setPosition(_rightHandRect.origin);
   
   _leftHand = Sprite::createWithSpriteFrameName("hand_left_1.png");
   aLayer->addChild(_leftHand,1);
   _leftHand->setAnchorPoint(Point(0,0));
   _leftHand->setScale(HscaleFactor);
   
   float xPos = chefOrigin.x + _chefRect.size.width - (handSize.width)/2.0f;
   _leftHandRect = Rect(_rightHandRect);
   _leftHandRect.origin.x = xPos;
   _leftHand->setPosition(_leftHandRect.origin);
   
   return true;
}

void Chef::setScale(float aScaleFactor)
{

}


cocos2d::Size Chef::getSize()
{
   return _chefRect.size;
}

void Chef::setOrigin(cocos2d::Point anOrigin)
{
   _chefRect.origin.x = anOrigin.x;
   _chefRect.origin.y = anOrigin.y;
   _rightHandRect.origin.x = anOrigin.x;
   _rightHandRect.origin.y = anOrigin.y;

   float xPos = anOrigin.x + _chefRect.size.width - (_leftHandRect.size.width)/2.0f;
   _leftHandRect.origin.x = xPos;
   _leftHandRect.origin.y = anOrigin.y;

   _chef->setPosition(_chefRect.origin);
   _leftHand->setPosition(_leftHandRect.origin);
   _rightHand->setPosition(_rightHandRect.origin);
}

