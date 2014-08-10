
#include "BaseIndicator.h"

USING_NS_CC;

bool BaseIndicator::init(const std::string& bgFrameName, const std::string& indicatorFrameName, bool isLeft, float score) {
    
    if ( !Layer::create() )
    {
        return false;
    }
    
    _bg = Sprite::createWithSpriteFrameName(bgFrameName);
    _bg->setPosition(Vec2(_bg->getContentSize().width/2, 0));
    this->addChild(_bg, 1);
    
    
    _indicator = Sprite::createWithSpriteFrameName(indicatorFrameName);
    _indicator->setAnchorPoint(Vec2(0, 0.5));
    _indicator->setScaleX(score);
    //_indicator->setContentSize(Size(_indicator->getContentSize().width * score / 100, _indicator->getContentSize().height));
    //_indicator->setPosition(Vec2(_bg->getContentSize().width/2, 0));
    this->addChild(_indicator, 0);
    
    _isLeft = isLeft;
    _score = score;
    
    return true;
}

void BaseIndicator::doStep(float score) {
    if (score > 1) score = 1;
    else if (score < 0) score = 0;
    _indicator->setScaleX(score);
}

bool BaseIndicator::isComplete() {
    return _indicator->getScaleX() == 1;
}