
#include "BaseGamePopup.h"

USING_NS_CC;

//BaseGamePopup::BaseGamePopup(){}
//BaseGamePopup::~BaseGamePopup() {}

bool BaseGamePopup::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite *bg = Sprite::createWithSpriteFrameName("bg_popup.png");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);
    
    cocos2d::Vector<cocos2d::MenuItem*> menuItems;

    this->initMenuItems(menuItems);

    Menu *mainMenu = Menu::createWithArray(menuItems);
    //mainMenu->alignItemsVerticallyWithPadding(10);
    mainMenu->alignItemsHorizontallyWithPadding(10);
    mainMenu->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y + 150));
    this->addChild(mainMenu, 1);

    return true;
}

void BaseGamePopup::initItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& spriteFrameName, const ccMenuCallback& callback) {

    MenuItem* item = MenuItemSprite::create(
                           Sprite::createWithSpriteFrameName(spriteFrameName),
                           Sprite::createWithSpriteFrameName(spriteFrameName),
                           callback);
    menuItems.pushBack(item);
}

void BaseGamePopup::changeScene(Scene* newScene) {
    TransitionFade *transition = TransitionFade::create(0.0f, newScene);
    Director::getInstance()->replaceScene(transition);
    Director::getInstance()->resume();
}

void BaseGamePopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems) {
    CCLOG("base");
}