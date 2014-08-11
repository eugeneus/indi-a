
#include "BaseMenuPopup.h"

USING_NS_CC;


void BaseMenuPopup::initMenuItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& name, const ccMenuCallback& callback, Vec2 pos) {
    Sprite* normal = Sprite::createWithSpriteFrameName(name);
    Sprite* selected = Sprite::createWithSpriteFrameName(name);
    MenuItemSprite *menuItem = MenuItemSprite::create(normal, selected, callback);//MenuItemFont::create(name, callback);
    menuItem->setPosition(pos);
    menuItems.pushBack(menuItem);
}

bool BaseMenuPopup::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cocos2d::Vector<cocos2d::MenuItem*> menuItems;
    
    initMenuItems(menuItems, origin, visibleSize);
   
    Menu *mainMenu = Menu::createWithArray(menuItems);
    //mainMenu->alignItemsVerticallyWithPadding(0);
    mainMenu->setAnchorPoint(Vec2(0,0));
    mainMenu->setPosition(Vec2(0,0));
    this->addChild(mainMenu, 1);
    
    // Sprite *spriteBg = Sprite::createWithSpriteFrameName("menu_bg.png");
    // spriteBg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // this->addChild(spriteBg, 0);
    
    return true;
}

void BaseMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
}

void BaseMenuPopup::changeScene(cocos2d::Scene *newScene) {
    TransitionFade *transition = TransitionFade::create(1.0f, newScene);
    Director::getInstance()->replaceScene(transition);
}
