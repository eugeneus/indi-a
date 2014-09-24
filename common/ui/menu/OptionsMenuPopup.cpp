
#include "OptionsMenuPopup.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "UserDataProvider.h"

USING_NS_CC;

OptionsMenuPopup* OptionsMenuPopup::create()
{
    OptionsMenuPopup *pRet = new OptionsMenuPopup();
    if (pRet && pRet->init())
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

void OptionsMenuPopup::initMenuItems(cocos2d::Vector<cocos2d::MenuItem *> &menuItems, cocos2d::Vec2 origin, cocos2d::Size visibleSize) {
    initMenuItem(menuItems, BTN_OPTION_MUSIC, CC_CALLBACK_1(OptionsMenuPopup::menuMusicCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 250));
    initMenuItemTrigger(menuItems, BTN_OPTION_MUSIC, CC_CALLBACK_1(OptionsMenuPopup::menuMusicCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 250), 0);
    
    initMenuItem(menuItems, BTN_OPTION_SOUND, CC_CALLBACK_1(OptionsMenuPopup::menuSoundCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 400));
    initMenuItemTrigger(menuItems, BTN_OPTION_SOUND, CC_CALLBACK_1(OptionsMenuPopup::menuSoundCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 400), 1);
    
    
    initMenuItem(menuItems, BTN_OPTION_NOTIF, CC_CALLBACK_1(OptionsMenuPopup::menuNotificationsCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 550));
    initMenuItemTrigger(menuItems, BTN_OPTION_NOTIF, CC_CALLBACK_1(OptionsMenuPopup::menuNotificationsCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 550), 2);
    
    initMenuItem(menuItems, BTN_ALL_BACK, CC_CALLBACK_1(OptionsMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 800));
}

bool isNeedRevertButtons(int tag) {
    bool isButtonOn = true;
    if (tag == 0) {
        isButtonOn = UserDataProvider::getInstance()->isMusicOn();
    } else if (tag == 1) {
        isButtonOn = UserDataProvider::getInstance()->isSoundOn();
    } else if (tag == 2) {
        isButtonOn = UserDataProvider::getInstance()->isNotificationOn();
    }
     
    
    return !isButtonOn;
}

void OptionsMenuPopup::initMenuItemTrigger(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& name, const ccMenuCallback& callback, Vec2 pos, int tag) {
    std::string spriteNormalFrameName = BTN_NAME_TRIGGER_ON(name);
    std::string spriteSelectedFrameName = BTN_NAME_TRIGGER_OFF(name);
   // if (!isFrameNameExist(spriteSelectedFrameName)) spriteSelectedFrameName = BTN_NAME(name);
    Sprite* normal = Sprite::createWithSpriteFrameName(spriteNormalFrameName);
    Sprite* selected = Sprite::createWithSpriteFrameName(spriteSelectedFrameName);
    
    bool isNeedButtonRevert = isNeedRevertButtons(tag);
    
    MenuItemSprite *menuItem;
    if (isNeedButtonRevert) {
        menuItem = MenuItemSprite::create(selected, normal, callback);
    } else {
        menuItem = MenuItemSprite::create(normal, selected, callback);
    }
    
    //MenuItemSprite *menuItem = MenuItemSprite::create(normal, selected, callback);
    menuItem->setPosition(pos);
    menuItem->setTag(tag);
    menuItems.pushBack(menuItem);
}

void OptionsMenuPopup::toggleMenuItemByTag(int tag, const std::string& name, bool isON) {
    Node* node = mainMenu->getChildByTag(tag);// Director::getInstance()->getRunningScene()->getChildByTag(tag);
    if (node) {
        MenuItemSprite* item = (MenuItemSprite*) node;
        
        std::string spriteNormalFrameName = isON ? BTN_NAME_TRIGGER_ON(name) : BTN_NAME_TRIGGER_OFF(name);
        std::string spriteSelectedFrameName = isON ? BTN_NAME_TRIGGER_OFF(name) : BTN_NAME_TRIGGER_ON(name);
        
        item->setNormalImage(Sprite::createWithSpriteFrameName(spriteNormalFrameName));
        item->setSelectedImage(Sprite::createWithSpriteFrameName(spriteSelectedFrameName));
    }
}

void OptionsMenuPopup::menuBackCallback(cocos2d::Ref* pSender) {
    Scene *newScene = MainMenu::createScene();
    this->changeScene(newScene);
}

void OptionsMenuPopup::menuMusicCallback(cocos2d::Ref* pSender) {
    float volume =  CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    if (volume > 0)
        volume = 0;
    else
        volume = 1;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    UserDataProvider::getInstance()->setMusicOn(volume == 1);
    this->toggleMenuItemByTag(0, BTN_OPTION_MUSIC, volume == 1);
}

void OptionsMenuPopup::menuSoundCallback(cocos2d::Ref* pSender) {
    float volume =  CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    if (volume > 0)
        volume = 0;
        else
            volume = 1;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    UserDataProvider::getInstance()->setSoundOn(volume == 1);
    this->toggleMenuItemByTag(1, BTN_OPTION_SOUND, volume == 1);
}

void OptionsMenuPopup::menuNotificationsCallback(cocos2d::Ref* pSender) {
    bool value = UserDataProvider::getInstance()->isNotificationOn();
    UserDataProvider::getInstance()->setNotificationOn(!value);
    this->toggleMenuItemByTag(2, BTN_OPTION_NOTIF, true);
}
