
#ifndef __Blind_Chef__MyJumpTo__
#define __Blind_Chef__MyJumpTo__

#include "cocos2d.h"

class MyJumpTo : public cocos2d::JumpBy {
public:
    /** creates the action */
    static MyJumpTo* create(float duration, const cocos2d::Vec2& position, float height, int jumps);
    
    //
    // Override
    //
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual MyJumpTo* clone() const override;
    virtual MyJumpTo* reverse(void) const override;
    
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    MyJumpTo() {}
    virtual ~MyJumpTo() {}
    
private:
    float _prevY = 0;
    float _waitTime = 0;
    float _time = 0;
    float _deltaTime = 0;
    float _prevT = 0;
    float _deltaY = 0;
    CC_DISALLOW_COPY_AND_ASSIGN(MyJumpTo);
};

#endif /* defined(__Blind_Chef__MyJumpTo__) */
