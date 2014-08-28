
#ifndef __BlindChef__BaseIndicator__
#define __BlindChef__BaseIndicator__

#include "cocos2d.h"

class BaseIndicator : public cocos2d::Layer {
protected:
    cocos2d::Sprite* _bg;
    cocos2d::Sprite* _indicator;
    
    bool _isLeft;
    float _score;

public:
    bool init(const std::string& bgFrameName, const std::string& indicatorFrameName, bool isLeft, float score);
    
    void doStep(float score);
    bool isComplete();
    
    virtual void restart();
};


#endif /* defined(__BlindChef__BaseIndicator__) */
