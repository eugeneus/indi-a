#include "BaseMenu.h"

USING_NS_CC;

bool BaseMenu::init(const std::string& pMenuTitle)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->initializeMenu();
    
    Layer* menuLayer = this->createMenuLayer();
    if (menuLayer) this->addChild(menuLayer, 0);
    
    if (pMenuTitle.size() > 0) {
        Sprite* bg = Sprite::createWithSpriteFrameName(pMenuTitle);
        bg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
        this->addChild(bg, -1);
    }
    return true;
}

cocos2d::Layer* BaseMenu::createMenuLayer() {
    return NULL;
}