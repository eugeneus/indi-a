
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
    super::addChild(bg1);
    
    float length = bg1->getContentSize().width;
    
    int count = (int)round(pLength/length + 1.5);
        
    for (int i=0; i<count; i++) {
        Sprite* bg = Sprite::createWithSpriteFrameName(bgSpriteFrameName);
        prevPos = Vec2(prevPos.x + length - 2, prevPos.y);
        bg->setPosition(prevPos);
        bg->setAnchorPoint(Vec2(0, 0));
        sprites.pushBack(bg);
        super::addChild(bg);
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
        sp->setPosition(Vec2(sp->getPosition().x - delta, sp->getPosition().y));
    }
    
    for(int i=0; i<children.size(); i++) {
        Node* node = children.at(i);
        node->setPosition(Vec2(node->getPosition().x - delta, node->getPosition().y));
    }
}

void Cyclable::stopCycling() {

}

void Cyclable::startCycling() {
    this->scheduleUpdate();
}

void Cyclable::changeCyclingSpeed(float speed) {
    
}

void Cyclable::addChild(cocos2d::Node* node, int zIndex) {
    super::addChild(node, zIndex);
    children.pushBack(node);
}

Vector<Node*> Cyclable::getChildrenItems() {
    return children;
}