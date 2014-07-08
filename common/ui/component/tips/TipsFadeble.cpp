
#include "TipsFadeble.h"

USING_NS_CC;

TipsFadeble* TipsFadeble::create(const std::string& bgFrameName, const std::string& tipsImgFrameName)
{
    TipsFadeble *pRet = new TipsFadeble();
    if (pRet && pRet->init(bgFrameName, tipsImgFrameName))
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

bool TipsFadeble::init(const std::string& bgFrameName, const std::string& tipsImgFrameName)
{
    if ( !Layer::create() )
    {
        return false;
    }
    
    this->setOpacity(0.0);
    this->setScale(0.5);
    
    bg = Sprite::createWithSpriteFrameName(bgFrameName);
    bg->setOpacity(0.0);
    this->addChild(bg, 0);
    
    
    img = Sprite::createWithSpriteFrameName(tipsImgFrameName);
    img->setOpacity(0.0);
    this->addChild(img, 1);
    
    return true;
}

void TipsFadeble::showTip() {
    float scale = 255;
    
    this->runAction(Sequence::create(FadeTo::create(2.0, scale), ScaleTo::create(2.0, 1.0), NULL));
    //this->runAction(FadeTo::create(2.0, scale));
    bg->runAction(FadeTo::create(2.0, scale));
    img->runAction(FadeTo::create(4.0, scale));
}

void TipsFadeble::hideTip() {
    this->runAction(Sequence::create(FadeTo::create(2.0, 0.0), ScaleTo::create(2.0, 0.5), NULL));
    //this->runAction(FadeTo::create(2.0, 0.0));
    bg->runAction(FadeTo::create(2.0, 0.0));
    img->runAction(FadeTo::create(2.0, 0.0));
}

void TipsFadeble::toggleTip() {
    GLubyte opacity = this->getOpacity();
    this->stopAllActions();
    bg->stopAllActions();
    img->stopAllActions();
    
    if (opacity == 0) {
        showTip();
    } else {
        hideTip();
    }
}
