
#ifndef __BlindChef__Spritable__
#define __BlindChef__Spritable__

#include "cocos2d.h"

using namespace std;

class Spritable : public cocos2d::Layer {
    
private:
    cocos2d::Sprite *animatedSprite;
    
protected:
    bool initWithSpriteAndPos(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    void createWalkAnimFrames(cocos2d::Vector<cocos2d::SpriteFrame*>& frames, int start, int spriteCount, const char *framesPattern, float delayTime);
    void animateSpriteFrames(cocos2d::Vector<cocos2d::SpriteFrame*>& animateFrames, float delayTime);
    void changeSpriteFramesAnimation(cocos2d::Vector<cocos2d::SpriteFrame*>& animateFrames, float delayTime);
public:
    Spritable();
    virtual ~Spritable();
    
    static Spritable* create(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
};

#endif /* defined(__BlindChef__Spritable__) */
