
#ifndef __Blind_Chef__MyBizeierMoveTo__
#define __Blind_Chef__MyBizeierMoveTo__

#include "cocos2d.h"
USING_NS_CC;

class MyBizeierMoveTo : public cocos2d::BezierBy {
public:
    
    static MyBizeierMoveTo* create(float t, cocos2d::ccBezierConfig& c);
    
    //
    // Overrides
    //
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual MyBizeierMoveTo* clone() const override;
    virtual MyBizeierMoveTo* reverse(void) const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    MyBizeierMoveTo() {}
    virtual ~MyBizeierMoveTo() {}
    
    bool initWithDuration(float t, const cocos2d::ccBezierConfig &c);
    
protected:
    cocos2d::ccBezierConfig _toConfig;
    bool _isCommon = false;
    float _myTime = 0;
    float _prevTime = 0;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(MyBizeierMoveTo);
};


#endif /* defined(__Blind_Chef__MyBizeierMoveTo__) */
