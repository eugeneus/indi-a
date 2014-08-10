
#include "Multiplier.h"


USING_NS_CC;

Multiplier::Multiplier(){}
Multiplier::~Multiplier() {}


Multiplier* Multiplier::create()
{
    
    Multiplier *pRet = new Multiplier();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool Multiplier::init() {
    
    if (!Layer::init()) {
        return false;
    }
    
    
    _count = 0;
    _itemId = -1;
    //_countLabel;
    
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 32;
    ttfConfig.fontFilePath = "RioGrande.ttf";
    _countLabel = Label::createWithTTF(ttfConfig, CCString::createWithFormat("x%i", _count)->getCString());
    _countLabel->setColor(Color3B(255, 200, 0));
    this->addChild(_countLabel);
    
    return true;
}

void Multiplier::updateLabel() {
    _countLabel->setString(CCString::createWithFormat("x%i", _count)->getCString());
}

int Multiplier::update(int pItemId) {
    if (_itemId == -1) {
        _itemId = pItemId;
    }
    
    if (pItemId == _itemId) {
        _count ++;
    } else {
        _count = 0;
    }
    
    updateLabel();
    
    return _count;
}

void Multiplier::reset() {
    _count = 0;
    updateLabel();
    _itemId = -1;
}

int Multiplier::getCount() {
    return _count;
}

