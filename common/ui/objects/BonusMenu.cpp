
#include "BonusMenu.h"
#include "ImageLabelMenuItem.h"
#include "LevelProvider.h"
#include "FoodFactory.h"
#include "Item.h"


USING_NS_CC;

BonusMenu* BonusMenu::create(LevelProvider* aLevelInfo)
{
    BonusMenu *pRet = new BonusMenu();
    if (pRet && pRet->init(aLevelInfo))
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

bool BonusMenu::init(LevelProvider* aLevelInfo)
{
    if ( !Layer::create() )
    {
        return false;
    }
    
    bonus1Count = Value(0);
    bonus2Count = Value(0);
    bonus3Count = Value(0);
    
    Item* bonusItem = FoodFactory::createFood(aLevelInfo->getBonusItems().at(0));
    
    bonus1 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus1Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus1Callback, this));
    
    //delete bonusItem;
    bonusItem = FoodFactory::createFood(aLevelInfo->getBonusItems().at(1));
    bonus2 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus2Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus2Callback, this));
    
    //delete bonusItem;
    bonusItem = FoodFactory::createFood(aLevelInfo->getBonusItems().at(2));
    bonus3 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus3Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus3Callback, this));
    //delete bonusItem;
    
    Menu* menu = Menu::create(bonus1, bonus2, bonus3, NULL);
    menu->alignItemsHorizontally();
    this->addChild(menu, 1);
    
    return true;
}

bool isCanUseBonus(Value bonusCount) {
    return bonusCount.asInt() > 0;
}

void BonusMenu::updateBonus(Value& bonusCount, int delta, ImageLabelMenuItem* bonusLabel) {
    bonusCount = Value(bonusCount.asInt() + delta);
    bonusLabel->changeLabelText(CCString::createWithFormat("x%i", bonusCount.asInt())->getCString());
}

void BonusMenu::changeBonusCount(int bonus_type, bool incr) {
    int delta = incr ? 1 : -1;
    
    switch(bonus_type)
    {
        case kBonusType1:
        {
            updateBonus(bonus1Count, delta, bonus1);
            break;
        }
        case kBonusType2:
        {
            updateBonus(bonus2Count, delta, bonus2);
            break;
        }
        case kBonusType3:
        {
            updateBonus(bonus3Count, delta, bonus3);
            break;
        }
        default:
        {
            break;
        }
    }
}

void BonusMenu::bonus1Callback(Ref* pSender) {
    CCLOG("bonus 1 click");
    
    if (isCanUseBonus(bonus1Count)) {
        updateBonus(bonus1Count, -1, bonus1);
        //run
    } else {
        //show store
    }
}

void BonusMenu::bonus2Callback(Ref* pSender) {
    CCLOG("bonus 2 click");
    
    if (isCanUseBonus(bonus2Count)) {
        updateBonus(bonus2Count, -1, bonus2);
        //run
    } else {
        //show store
    }
}

void BonusMenu::bonus3Callback(Ref* pSender) {
    CCLOG("bonus 3 click");
    
    if (isCanUseBonus(bonus3Count)) {
        updateBonus(bonus3Count, -1, bonus3);
        //run
    } else {
        //show store
    }
}