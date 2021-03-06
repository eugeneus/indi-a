
#ifndef __BlindChef__Spritable__
#define __BlindChef__Spritable__

#include "cocos2d.h"

using namespace std;

class Spritable : public cocos2d::Sprite {
    
private:
    //cocos2d::Sprite *animatedSprite;
    cocos2d::Size _defaultContentSize;
   
   
protected:
    bool initWithSpriteAndPos(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
   
    void createWalkAnimFrames(cocos2d::Vector<cocos2d::SpriteFrame*>& frames, int start, int spriteCount, const char *framesPattern, float delayTime);
    void animateSpriteFrames(cocos2d::Vector<cocos2d::SpriteFrame*>& animateFrames, float delayTime);
   
    void changeSpriteFramesAnimation(cocos2d::Vector<cocos2d::SpriteFrame*>& animateFrames, float delayTime);
   
    void testDraw();
   
   float _defaultScale;
public:
    Spritable();
    virtual ~Spritable();
   
   cocos2d::Size getDefaultContentSize();
   cocos2d::Size getScaledContentSize();
   void setSpriteSize(cocos2d::Size aSize);
   void setDefaultSize();
   void applyDefaultScale();
   
    cocos2d::Point _recentPos;
    float _speedFactor;
    
    float getSpeedFactor();
    
    //virtual void update(float delta);


   static Spritable* create(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
};

#endif /* defined(__BlindChef__Spritable__) */
