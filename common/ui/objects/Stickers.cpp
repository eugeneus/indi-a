
#include "Stickers.h"
#include "Dish.h"

USING_NS_CC;

Stickers* Stickers::create()
{
    Stickers *pRet = new Stickers();
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

Sprite *createSprite(const std::string& filename, float xPos, const std::string& labelText) {
    TTFConfig ttf32;
    ttf32.fontSize = 10;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorYellow = Color3B(0, 0, 0);
    Label *label = Label::createWithTTF(ttf32, labelText);
    label->setColor(colorYellow);

    
    Sprite *sprite = Sprite::create(filename);
    sprite->setPosition(Vec2(sprite->getContentSize().width/2 + xPos, sprite->getPosition().y));

    label->setPosition(Vec2(label->getPosition().x + sprite->getContentSize().width/2, label->getPosition().y + sprite->getContentSize().height/2));
    sprite->addChild(label, 1);
    return sprite;
}

bool Stickers::init() {
    
    if(!Layer::init()) {//LayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    
    _first = createSprite("sticker_1.png", 20, "1");
    _next1 = createSprite("sticker_2.png", 350, "2");
    _next2 = createSprite("sticker_3.png", 420, "3");
    _next3 = createSprite("sticker_4.png", 490,"4");
    _last = createSprite("sticker_5.png", 560, "");
    this->addChild(_first);
    this->addChild(_next1);
    this->addChild(_next2);
    this->addChild(_next3);
    this->addChild(_last);
    
    this->setContentSize(Size(this->getContentSize().width, _first->getContentSize().height+ 10));

    return true;
}

void reInitSticker(Sprite *spr, const std::string& labelText) {
    Node *child = spr->getChildren().at(0);
    
    if (child) {
        Label *label = (Label *) child;
        label->setString(labelText);
    }
}

void Stickers::setupQueue(std::vector<Dish *> queue) {
    reInitSticker(_first, queue.at(0)->getImageName());
    reInitSticker(_next1, queue.at(1)->getImageName());
    reInitSticker(_next2, queue.at(2)->getImageName());
    reInitSticker(_next3, queue.at(3)->getImageName());
}