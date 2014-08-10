
#include "ImageLabelMenuItem.h"

USING_NS_CC;

ImageLabelMenuItem* ImageLabelMenuItem::create(const std::string& text, const std::string& imageFrameName, const ccMenuCallback& callback)
{
    ImageLabelMenuItem *pRet = new ImageLabelMenuItem();
    if (pRet && pRet->init(text, imageFrameName, callback))
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

bool ImageLabelMenuItem::init(const std::string& text, const std::string& imageFrameName, const ccMenuCallback& callback)
{
    
    Sprite* normalMenuItemSprite = Sprite::createWithSpriteFrameName(imageFrameName);
    Sprite* selectedMenuItemSprite = Sprite::createWithSpriteFrameName(imageFrameName);
    Sprite* disabledMenuItemSprite = Sprite::createWithSpriteFrameName(imageFrameName);
    
    if ( !MenuItemSprite::initWithNormalSprite(normalMenuItemSprite, selectedMenuItemSprite, disabledMenuItemSprite, callback) )
    {
        return false;
    }
    
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 32;
    ttfConfig.fontFilePath = "RioGrande.ttf";
    label = Label::createWithTTF(ttfConfig, text);
    label->setColor(Color3B(255, 200, 0));
    label->setPosition(Vec2(label->getPosition().x + normalMenuItemSprite->getContentSize().width,label->getPosition().y));
    this->addChild(label, 1);
    
    
    return true;
}

void ImageLabelMenuItem::changeLabelText(const std::string& text) {

}