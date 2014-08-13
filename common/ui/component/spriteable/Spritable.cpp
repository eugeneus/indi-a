
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

   if ( !Sprite::initWithSpriteFrameName(spriteFrameName) ) //!LayerColor::initWithColor(ccc4(255, 255, 255, 255))
    {
        return false;
    }

   
   _defaultScale = 1.0f;
    //animatedSprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
    //animatedSprite->setAnchorPoint(Vec2(0, 0));
    
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->_defaultContentSize = this->getContentSize();
    this->setContentSize(_defaultContentSize);
    //this->addChild(animatedSprite);
    
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
    //animatedSprite->runAction(repeatAction);
   this->runAction(repeatAction);
}

void Spritable::changeSpriteFramesAnimation(Vector<SpriteFrame*>& animateFrames, float delayTime)
{
    //animatedSprite->stopActionByTag(333);
   this->stopActionByTag(333);
    
    this->animateSpriteFrames(animateFrames, delayTime);
}

void Spritable::createWalkAnimFrames(Vector<SpriteFrame*>& animateFrames, int start, int spriteCount, const char *framesPattern, float delayTime)
{
    for(int i = start; i < start + spriteCount; ++i) {
        const char *frameName = CCString::createWithFormat(framesPattern, i)->getCString();
        SpriteFrame* animFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        
        //auto animFrame = SpriteFrame::create(frameName, animatedSprite->getBoundingBox()); //Rect(0,0,40,40));
        animateFrames.pushBack(animFrame);
        //animFrame->release(); // causes an retain count accert!
    }
}

cocos2d::Size Spritable::getScaledContentSize()
{
   Size size = this->getContentSize();
   float scale = this->getScale();
   size.width = size.width * scale;
   size.height = size.height * scale;
   
   return size;
}

Size Spritable::getDefaultContentSize()
{
   return _defaultContentSize;
}

void Spritable::applyDefaultScale()
{
   this->setScale(_defaultScale);
}

void Spritable::setDefaultSize()
{
   //this->animatedSprite->setContentSize(_defaultContentSize);
   
   this->setContentSize(_defaultContentSize);
   this->setContentSize(_defaultContentSize);
   this->applyDefaultScale();
   
}


void Spritable::setSpriteSize(Size aSize)
{
   this->_defaultContentSize = aSize;
   //this->animatedSprite->setContentSize(_defaultContentSize);
   this->setContentSize(_defaultContentSize);
   this->setContentSize(_defaultContentSize);
}

void Spritable::testDraw()
{
   // draw anchor point
   DrawNode *dotAnchorNode = DrawNode::create();
   dotAnchorNode->drawDot(this->getAnchorPointInPoints(), 10, Color4F(Color3B::WHITE));
   this->addChild(dotAnchorNode, 0);
   // draw position poing
   DrawNode *dotPositinNode = DrawNode::create();
   dotPositinNode->drawDot(this->getPosition(), 10, Color4F(Color3B::WHITE));
   this->addChild(dotPositinNode, 0);
   // draw content rect
   
   DrawNode *rectNode = DrawNode::create();
   Size imgSize = this->getContentSize();
   Point originPos = this->getPosition();
   Point point1 = originPos;
   point1.x += imgSize.width;
   Point point2 = point1;
   point2.y += imgSize.height;
   Point point3 = point2;
   point3.x = originPos.x;
   Point verts1 [] = {originPos,point1,point2,point3};
   
   rectNode->drawPolygon(verts1, 4, Color4F(1,1,1,0.2), 1.0, Color4F(Color3B::WHITE));
   this->addChild(rectNode, 0);
}



