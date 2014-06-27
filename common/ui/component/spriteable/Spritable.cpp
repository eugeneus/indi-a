
#include "Spritable.h"


USING_NS_CC;

Spritable::Spritable(){}
Spritable::~Spritable() {}


Spritable* Spritable::create(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime)
{
    
    Spritable *pRet = new Spritable();
    
    if (pRet && pRet->initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool Spritable::initWithSpriteAndPos(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime)
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    animatedSprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
    animatedSprite->setAnchorPoint(Vec2(0, 0));
    
    this->setAnchorPoint(Vec2(0, 0));
    this->setContentSize(animatedSprite->getContentSize());
    this->addChild(animatedSprite);
    
    Vector<SpriteFrame*> frames;
    
    this->createWalkAnimFrames(frames, 1, spriteCount, framesPattern, deleayTime);
    this->animateSpriteFrames(frames, deleayTime);
        
    return true;
}

void Spritable::animateSpriteFrames(Vector<SpriteFrame*>& animateFrames, float delayTime)
{
    Animation *animation = Animation::createWithSpriteFrames(animateFrames, delayTime);
    RepeatForever *repeatAction = RepeatForever::create(Animate::create(animation));
    repeatAction->setTag(333);
    animatedSprite->runAction(repeatAction);
}

void Spritable::changeSpriteFramesAnimation(Vector<SpriteFrame*>& animateFrames, float delayTime)
{
    animatedSprite->stopActionByTag(333);
    
    this->animateSpriteFrames(animateFrames, delayTime);
}

void Spritable::createWalkAnimFrames(Vector<SpriteFrame*>& animateFrames, int start, int spriteCount, const char *framesPattern, float delayTime)
{
    for(int i = start; i < start + spriteCount; ++i) {
        const char *frameName = CCString::createWithFormat(framesPattern, i)->getCString();
        SpriteFrame* animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        
        //auto animFrame = SpriteFrame::create(frameName, animatedSprite->getBoundingBox()); //Rect(0,0,40,40));
        animateFrames.pushBack(animFrame);
        animFrame->release();
    }
}
