
#include "OptionsMenuPopup.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

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
    initMenuItemTrigger(menuItems, BTN_OPTION_MUSIC_ON, CC_CALLBACK_1(OptionsMenuPopup::menuMusicCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 250), 0);
    
    initMenuItem(menuItems, BTN_OPTION_SOUND, CC_CALLBACK_1(OptionsMenuPopup::menuSoundCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 400));
    initMenuItemTrigger(menuItems, BTN_OPTION_SOUND_ON, CC_CALLBACK_1(OptionsMenuPopup::menuSoundCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 400), 1);
    
    
    initMenuItem(menuItems, BTN_OPTION_NOTIF, CC_CALLBACK_1(OptionsMenuPopup::menuNotificationsCallback, this), Vec2(visibleSize.width/2 + origin.x - 50, visibleSize.height + origin.y - 550));
    initMenuItemTrigger(menuItems, BTN_OPTION_NOTIF_ON, CC_CALLBACK_1(OptionsMenuPopup::menuNotificationsCallback, this), Vec2(visibleSize.width/2 + origin.x + 190, visibleSize.height + origin.y - 550), 2);
    
    initMenuItem(menuItems, BTN_ALL_BACK, CC_CALLBACK_1(OptionsMenuPopup::menuBackCallback, this), Vec2(origin.x + 100, visibleSize.height + origin.y - 800));
}

void OptionsMenuPopup::initMenuItemTrigger(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& name, const ccMenuCallback& callback, Vec2 pos, int tag) {
    std::string spriteNormalFrameName = BTN_NAME(name);
    std::string spriteSelectedFrameName = BTN_NAME_SELECTED(name);
    if (!isFrameNameExist(spriteSelectedFrameName)) spriteSelectedFrameName = BTN_NAME(name);
    Sprite* normal = Sprite::createWithSpriteFrameName(spriteNormalFrameName);
    Sprite* selected = Sprite::createWithSpriteFrameName(spriteSelectedFrameName);
    MenuItemSprite *menuItem = MenuItemSprite::create(normal, selected, callback);//MenuItemFont::create(name, callback);
    menuItem->setPosition(pos);
    menuItem->setTag(tag);
    menuItems.pushBack(menuItem);
}

void OptionsMenuPopup::toggleMenuItemByTag(int tag, const char* format, bool isON) {
    Node* node = mainMenu->getChildByTag(tag);// Director::getInstance()->getRunningScene()->getChildByTag(tag);
    if (node) {
        MenuItemSprite* item = (MenuItemSprite*) node;
        const std::string& imageName = CCString::createWithFormat(format, isON ? "on" : "off")->getCString();
        std::string spriteNormalFrameName = BTN_NAME(imageName);
        std::string spriteSelectedFrameName = BTN_NAME_SELECTED(imageName);
        if (!isFrameNameExist(spriteSelectedFrameName)) spriteSelectedFrameName = BTN_NAME(imageName);
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
    this->toggleMenuItemByTag(0, "btn_opt_music_%s", volume == 1);
}

void OptionsMenuPopup::menuSoundCallback(cocos2d::Ref* pSender) {
    float volume =  CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    if (volume > 0)
        volume = 0;
        else
            volume = 1;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
    this->toggleMenuItemByTag(1, "btn_opt_sound_%s", volume == 1);
}

void OptionsMenuPopup::menuNotificationsCallback(cocos2d::Ref* pSender) {
    this->toggleMenuItemByTag(2, "btn_opt_notif_%s", true);
}
