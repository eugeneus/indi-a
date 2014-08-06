
#ifndef __BlindChef__TouchController__
#define __BlindChef__TouchController__

#include "cocos2d.h"
USING_NS_CC;

class TouchController : public cocos2d::Ref {
private:
    cocos2d::Layer* _gameLayer;
    
    float _moveSpeed;
    float _startTime;
    cocos2d::Vec2 _startPos;
    
    bool _isItemDetected = false;

public:
    TouchController();
    
    ~TouchController();
    
    static TouchController* createWithLayer(cocos2d::Layer* aGameLayer);
    
    bool initWithLayer(cocos2d::Layer* aGameLayer);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event);
    
};

#endif /* defined(__BlindChef__TouchController__) */
