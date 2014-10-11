
#include "MyJumpTo.h"
#include "Item.h"
USING_NS_CC;

MyJumpTo* MyJumpTo::create(float duration, const Vec2& position, float height, int jumps)
{
    MyJumpTo *jumpTo = new MyJumpTo();
    jumpTo->initWithDuration(duration, position, height, jumps);
    jumpTo->autorelease();
    
    return jumpTo;
}

MyJumpTo* MyJumpTo::clone() const
{
    // no copy constructor
    auto a = new MyJumpTo();
    a->initWithDuration(_duration, _delta, _height, _jumps);
    a->autorelease();
    return a;
}

MyJumpTo* MyJumpTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in JumpTo");
    return nullptr;
}

void MyJumpTo::startWithTarget(Node *target)
{
    JumpBy::startWithTarget(target);
    _delta = Vec2(_delta.x - _startPosition.x, _delta.y - _startPosition.y);
}


void MyJumpTo::update(float t)
{
    if (_target)
    {
        float frac = fmodf( t * _jumps, 1.0f );
        
        
        
        
        CCLOG("----- %f", frac);
        if (true) {// (frac < 0.45 || frac > 0.55) {
        
        float y = _height * 4 * frac * (1 - frac);
        y += _delta.y * t;
        
            CCLOG("---- delta Y : %f, %f", _prevY, y);
            if (y - _prevY >= 0) {
                
                Item *item = (Item *)_target;
                
                
                
                Speed *speed = (Speed *) item->getActionByTag(666);
                if (speed) speed->setSpeed(0.7 - frac);
                
            } else {
                Item *item = (Item *)_target;
                
                
                
                Speed *speed = (Speed *) item->getActionByTag(666);
                if (speed) speed->setSpeed(frac >= 1.0 ? 1.0 : frac);
            }
            
            
            _prevY = y;
            
        float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        
        Vec2 diff = currentPos - _previousPos;
        _startPosition = diff + _startPosition;
        
        Vec2 newPos = _startPosition + Vec2(x,y);
        _target->setPosition(newPos);
        
        _previousPos = newPos;
#else
        _target->setPosition(_startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
        } else {
            float x = _delta.x * t;

            Vec2 currentPos = _target->getPosition();
            
            Vec2 diff = currentPos - _previousPos;
            _startPosition = diff + _startPosition;
            
            Vec2 newPos = Vec2(_startPosition.x + x, currentPos.y);//_startPosition + Vec2(x,currentPos.y);
            _target->setPosition(newPos);
            
            _previousPos = newPos;
        }
    }
}