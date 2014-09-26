
#include "BaseGamePopup.h"
#include "ResourcesManager.h"

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
    
    float bottomOffset = ResourcesManager::getInstance()->getBottomOffset();
    
    this->setPosition(Vec2(this->getPosition().x, this->getPosition().y + bottomOffset/2));

    return true;
}

void BaseGamePopup::initItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& spriteFrameName, const ccMenuCallback& callback) {

    std::string spriteNormalFrameName = BTN_NAME(spriteFrameName);
    std::string spriteSelectedFrameName = BTN_NAME_SELECTED(spriteFrameName);
    if (!SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteSelectedFrameName)) spriteSelectedFrameName = BTN_NAME(spriteFrameName);
    
    MenuItem* item = MenuItemSprite::create(
                           Sprite::createWithSpriteFrameName(spriteNormalFrameName),
                           Sprite::createWithSpriteFrameName(spriteSelectedFrameName),
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

void BaseGamePopup::addLabel(cocos2d::Node* target, const cocos2d::TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color, float posX, float posY, int tag) {
    Label* label = this->createLabel(ttfConfig, text, color);
    label->setPosition(Vec2(posX, posY));
    label->setTag(tag);
    target->addChild(label);
}

Label* BaseGamePopup::createLabel(const TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color) {
    Label* label = Label::createWithTTF(ttfConfig, text);
    //label->setAlignment(TextHAlignment::LEFT);
    //label->setLineBreakWithoutSpace(0);
    label->setAnchorPoint(Vec2(0,0));
    label->setColor(color);
    return label;
}

void BaseGamePopup::addLabelsLine(cocos2d::Node* target, cocos2d::Label* label1, cocos2d::Label* label2, float posX, float posY) {
    float length1 = label1->getContentSize().width;
    float length2 = label2->getContentSize().width;
    float dist = 20;
    float offsetX = (length1 + dist + length2)/2;
    
    label1->setPosition(Vec2(posX - offsetX, posY));
    label2->setPosition(Vec2(posX - offsetX + length1 + dist, posY));
    
    target->addChild(label1);
    target->addChild(label2);
    
}