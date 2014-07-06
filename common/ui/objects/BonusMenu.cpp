
#include "BonusMenu.h"
#include "ImageLabelMenuItem.h"

USING_NS_CC;

BonusMenu* BonusMenu::create()
{
    BonusMenu *pRet = new BonusMenu();
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

bool BonusMenu::init()
{
    if ( !Layer::create() )
    {
        return false;
    }
    
    ImageLabelMenuItem* bonus1 = ImageLabelMenuItem::create("x3", "bonus_1.png", CC_CALLBACK_1(BonusMenu::bonus1Callback, this));
    ImageLabelMenuItem* bonus2 = ImageLabelMenuItem::create("x2", "bonus_2.png", CC_CALLBACK_1(BonusMenu::bonus2Callback, this));
    ImageLabelMenuItem* bonus3 = ImageLabelMenuItem::create("x0", "bonus_3.png", CC_CALLBACK_1(BonusMenu::bonus3Callback, this));
    
    Menu* menu = Menu::create(bonus1, bonus2, bonus3, NULL);
    menu->alignItemsHorizontally();
    this->addChild(menu, 1);
    
    return true;
}

void BonusMenu::bonus1Callback(Ref* pSender) {
    CCLOG("bonus 1 click");
}

void BonusMenu::bonus2Callback(Ref* pSender) {
    CCLOG("bonus 2 click");
}

void BonusMenu::bonus3Callback(Ref* pSender) {
    CCLOG("bonus 3 click");
}