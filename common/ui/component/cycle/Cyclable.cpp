
#include "Cyclable.h"


USING_NS_CC;

Cyclable::Cyclable(){}
Cyclable::~Cyclable() {}


Cyclable* Cyclable::create(const char* bgSpriteFrameName, float speed, float length)
{
    
    Cyclable *pRet = new Cyclable();
    
    if (pRet && pRet->init(bgSpriteFrameName, speed, length))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool Cyclable::init(const char* bgSpriteFrameName, float pSpeed, float pLength) {
    
    if ( !LayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }
   
   this->setColor(ccc3(255, 255, 255));
   
   this->setAnchorPoint(Vec2(0,0));

   Sprite* bg1 = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
   this->setContentSize(bg1->getContentSize());
   
   endPoint = pLength;
   cyclingSpeed = pSpeed;
   
   float imgLen = bg1->getContentSize().width;
   
   Vec2 posOffset = Vec2(imgLen, 0);
   
   Vec2 prevPos = Vec2(0, 0);
   bg1->setAnchorPoint(Vec2(0, 0));
   bg1->setPosition(prevPos);

   sprites.pushBack(bg1);
   super::addChild(bg1);

   Sprite* bg2 = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
   bg2->setAnchorPoint(Vec2(0, 0));
   bg2->setPosition(Vec2(prevPos.x+imgLen-2,prevPos.y));
   
   sprites.pushBack(bg2);
   super::addChild(bg2);
    
    Sprite* bg3 = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
    bg3->setAnchorPoint(Vec2(0, 0));
    bg3->setPosition(Vec2(bg2->getPosition().x+imgLen-2,bg2->getPosition().y));
    
    sprites.pushBack(bg3);
    super::addChild(bg3);

    /*int count = (int)round(pLength/imgLen + 1.5);
   
    for (int i=0; i<count; i++) {
        Sprite* bg = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
        prevPos = Vec2(prevPos.x + imgLen - 2, prevPos.y);
        bg->setPosition(prevPos);
        bg->setAnchorPoint(Vec2(0, 0));
        sprites.pushBack(bg);
        super::addChild(bg);
    }
*/
    actionLength = endPoint;
    actionDuration = actionLength/cyclingSpeed;
   
    this->startCycling();
    
    return true;
}

void Cyclable::stopCycling() {
   
   //stopActions

}

void Cyclable::startCycling() {
   // Check for double restart (action runs twise)
   FiniteTimeAction* actionMoveBy = nullptr;
   FiniteTimeAction* actionPlase = nullptr;
   Vec2 v;
   for(Sprite* nSprite : sprites){
       
       nSprite->stopAllActions();
       actionMoveBy = CCMoveBy::create(actionDuration,Vec2(-actionLength, 0.0f));
       v = Vec2(nSprite->getPosition().x,nSprite->getPosition().y);
       actionPlase = Place::create(v);
       RepeatForever* cyclable = RepeatForever::create(Sequence::create(actionMoveBy,actionPlase, NULL));
       cyclable->setTag(1);
       nSprite->runAction(cyclable);
   }
   
}

void Cyclable::changeCyclingSpeed(float speed) {
    float imgLen = sprites.at(0)->getContentSize().width;
    Vec2 prevPos = Vec2(0, 0);
    for(Sprite* nSprite : sprites){
        nSprite->stopAllActions();
        nSprite->unscheduleAllSelectors();
        nSprite->setPosition(prevPos);
        prevPos.x = prevPos.x + (imgLen - 2);
    }
    
    cyclingSpeed = speed;
    actionDuration = actionLength/cyclingSpeed;
    this->startCycling();
}

void Cyclable::addChild(cocos2d::Node* node, int zIndex) {
    super::addChild(node, zIndex);
    children.pushBack(node);
}

Vector<Node*> Cyclable::getChildrenItems() {
    return children;
}