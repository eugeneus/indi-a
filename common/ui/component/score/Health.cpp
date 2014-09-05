
#include "Health.h"
USING_NS_CC;

Health::Health() {}
Health::~Health() {}

Health* Health::create(int pCount) {
    Health *pRet = new Health();
    
    if (pRet && pRet->init(pCount))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool Health::init(int pCount) {
    if (!Layer::init()) {
        return false;
    }
    
    count = pCount;
   
    Sprite* health = Sprite::createWithSpriteFrameName("health.png");
    health->setPosition(Vec2(health->getPosition().x + 40, health->getPosition().y - 40 - health->getContentSize().height/2));
    this->addChild(health);
    
    TTFConfig ttf32;
    ttf32.fontSize = 32;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorYellow = Color3B(255, 240, 104);
    label = Label::createWithTTF(ttf32, CCString::createWithFormat("x%i", count)->getCString());
    //label->setAnchorPoint(Vec2(0,40));
    label->setPosition(Vec2(health->getPosition().x + health->getContentSize().width, health->getPosition().y));
    label->setColor(colorYellow);
    this->addChild(label);
    
    return true;
}