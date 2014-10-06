
#include "BonusMenu.h"
#include "ImageLabelMenuItem.h"
#include "LevelProvider.h"
#include "FoodFactory.h"
#include "Item.h"
#include "SoundsConstants.h"
#include "UserDataProvider.h"
#include "PurchaseManager.h"

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
    
    _activeBonus = 0;
    
    UserDataProvider* userData = UserDataProvider::getInstance();
    
    bonus1Count = Value(userData->getBonus1Count());
    bonus2Count = Value(userData->getBonus2Count());
    bonus3Count = Value(userData->getBonus3Count());
    
    std::map<int,int> bonuses = aLevelInfo->getBonusItems();
    for (auto bonus : bonuses) {
        _bonusItemIds.push_back(bonus.first);
    }
    
    Item* bonusItem = FoodFactory::createFood(_bonusItemIds.at(kBonusType1 - 1));
    
    bonus1 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus1Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus1Callback, this));
    
    _bonus1PickUpSoundFile = SOUND_BONUS_LEMON;
    //delete bonusItem;
    bonusItem = FoodFactory::createFood(_bonusItemIds.at(kBonusType2 - 1));
    bonus2 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus2Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus2Callback, this));
    _bonus2PickUpSoundFile = SOUND_BONUS_SLOW_START;
    
    //delete bonusItem;
    bonusItem = FoodFactory::createFood(_bonusItemIds.at(kBonusType3 - 1));
    bonus3 = ImageLabelMenuItem::create(CCString::createWithFormat("x%i", bonus3Count.asInt())->getCString(),
                                        bonusItem->getSpriteFrameName(), CC_CALLBACK_1(BonusMenu::bonus3Callback, this));
    //delete bonusItem;
    _bonus3PickUpSoundFile = SOUND_BONUS_PICKUP;
    
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
    UserDataProvider* userData = UserDataProvider::getInstance();
    
    
    switch(bonus_type)
    {
        case kBonusType1:
        {
            userData->updateBonus1Count(bonus1Count.asInt() + delta);
            updateBonus(bonus1Count, delta, bonus1);
            break;
        }
        case kBonusType2:
        {
            userData->updateBonus2Count(bonus2Count.asInt() + delta);
            updateBonus(bonus2Count, delta, bonus2);
            break;
        }
        case kBonusType3:
        {
            userData->updateBonus3Count(bonus3Count.asInt() + delta);
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
    this->playBonus1PickUpSound();
    if (isCanUseBonus(bonus1Count)) {
        if (_activeBonus == 0) {
            updateBonus(bonus1Count, -1, bonus1);
            _activeBonus = kBonusType1;
            UserDataProvider::getInstance()->updateBonus1Count(bonus1Count.asInt() - 1);
        }
    } else {
        //show store
        [PurchaseManager purchaseBonus];
    }
}

void BonusMenu::bonus2Callback(Ref* pSender) {
    CCLOG("bonus 2 click");
    this->playBonus2PickUpSound();
    if (isCanUseBonus(bonus2Count)) {
        if (_activeBonus == 0) {
            updateBonus(bonus2Count, -1, bonus2);
            _activeBonus = kBonusType2;
            UserDataProvider::getInstance()->updateBonus2Count(bonus2Count.asInt() - 1);
        }

    } else {
        //show store
        [PurchaseManager purchaseBonus];
    }
}

void BonusMenu::bonus3Callback(Ref* pSender) {
    CCLOG("bonus 3 click");
    this->playBonus3PickUpSound();
    if (isCanUseBonus(bonus3Count)) {
        if (_activeBonus == 0) {
            updateBonus(bonus3Count, -1, bonus3);
            _activeBonus = kBonusType3;
            UserDataProvider::getInstance()->updateBonus3Count(bonus3Count.asInt() - 1);
        }
        
        //run
    } else {
        //show store
        [PurchaseManager purchaseBonus];
    }
}

bool BonusMenu::checkItemToUpdateBonus(Item* anItem)
{
    bool isBonusItem = false;
    int idxBonus = 0;

    while (idxBonus < _bonusItemIds.size() && !isBonusItem) {
        isBonusItem = _bonusItemIds.at(idxBonus) == anItem->getItemId();
        idxBonus++;
    }
    
    if (isBonusItem) {
        switch (idxBonus) {
            case kBonusType1:
                this->updateBonus(bonus1Count, 1, bonus1);
                UserDataProvider::getInstance()->updateBonus1Count(bonus1Count.asInt() + 1);
                break;
            case kBonusType2:
                this->updateBonus(bonus2Count, 1, bonus2);
                UserDataProvider::getInstance()->updateBonus2Count(bonus2Count.asInt() + 1);
                break;
            case kBonusType3:
                this->updateBonus(bonus3Count, 1, bonus3);
                UserDataProvider::getInstance()->updateBonus3Count(bonus3Count.asInt() + 1);
                break;
                
            default:
                break;
        }
    }
    
    return isBonusItem;
}

int BonusMenu::getActiveBonus()
{
    return _activeBonus;
}

void BonusMenu::resetActiveBonus()
{
    _activeBonus = 0;
}

void BonusMenu::playBonus1PickUpSound()
{
    if(!this->_bonus1PickUpSoundFile.empty()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(this->_bonus1PickUpSoundFile.c_str());
    }
}

void BonusMenu::playBonus2PickUpSound()
{
    if(!this->_bonus2PickUpSoundFile.empty()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(this->_bonus2PickUpSoundFile.c_str());
    }
}

void BonusMenu::playBonus3PickUpSound()
{
    if(!this->_bonus3PickUpSoundFile.empty()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(this->_bonus3PickUpSoundFile.c_str());
    }
}

