
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
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    endPoint = pLength;
    cyclingSpeed = pSpeed;
    
    Sprite* bg1 = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
    Vec2 prevPos = Vec2(0, bg1->getPosition().y - bg1->getContentSize().height);
    bg1->setPosition(prevPos);
    bg1->setAnchorPoint(Vec2(0, 0));
    sprites.pushBack(bg1);
    this->addChild(bg1);
    
    float length = bg1->getContentSize().width;
    
    int count = (int)round(pLength/length + 1.5);
        
    for (int i=0; i<count; i++) {
        Sprite* bg = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
        prevPos = Vec2(prevPos.x + length, prevPos.y);
        bg->setPosition(prevPos);
        bg->setAnchorPoint(Vec2(0, 0));
        sprites.pushBack(bg);
        this->addChild(bg);
    }
   
    this->startCycling();
    
    return true;
}

void Cyclable::update(float dt) {
    Sprite* first = sprites.front();
    Sprite* last = sprites.back();
    
    float delta = endPoint/cyclingSpeed; //TODO: speed
    
    if (last->getPosition().x - endPoint <= delta ) {
        first->setPosition(Vec2(last->getPosition().x + last->getContentSize().width, last->getPosition().y));
        
        Vector<Sprite*> tmpSprites;
        for(int i=1; i<sprites.size(); i++) {
            Sprite* sp = sprites.at(i);
            tmpSprites.pushBack(sp);
        }
        
        tmpSprites.pushBack(first);
        sprites.clear();
        sprites.pushBack(tmpSprites);
    }
    
    for(int i=0; i<sprites.size(); i++) {
        Sprite* sp = sprites.at(i);
       // sp->runAction(MoveTo::create(0,0, <#const cocos2d::Vec2 &position#>));
        sp->setPosition(Vec2(sp->getPosition().x - delta, sp->getPosition().y));
    }
}

void Cyclable::stopCycling() {

}

void Cyclable::startCycling() {
    this->scheduleUpdate();
}

void Cyclable::changeCyclingSpeed(float speed) {
    
}