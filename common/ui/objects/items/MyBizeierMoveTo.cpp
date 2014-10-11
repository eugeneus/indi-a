

#include "MyBizeierMoveTo.h"

USING_NS_CC;

MyBizeierMoveTo* MyBizeierMoveTo::create(float t, cocos2d::ccBezierConfig& c)
{
    MyBizeierMoveTo *bezierTo = new MyBizeierMoveTo();
    bezierTo->initWithDuration(t, c);
    bezierTo->autorelease();
    
    return bezierTo;
}

bool MyBizeierMoveTo::initWithDuration(float t, const ccBezierConfig &c)
{
    if (ActionInterval::initWithDuration(t))
    {
        _toConfig = c;
        _isCommon = true;
        _myTime = 0;
        return true;
    }
    
    return false;
}

MyBizeierMoveTo* MyBizeierMoveTo::clone() const
{
    // no copy constructor
    auto a = new MyBizeierMoveTo();
    a->initWithDuration(_duration, _toConfig);
    a->autorelease();
    return a;
}

void MyBizeierMoveTo::startWithTarget(Node *target)
{
    BezierBy::startWithTarget(target);
    _config.controlPoint_1 = _toConfig.controlPoint_1 - _startPosition;
    _config.controlPoint_2 = _toConfig.controlPoint_2 - _startPosition;
    _config.endPosition = _toConfig.endPosition - _startPosition;
}

MyBizeierMoveTo* MyBizeierMoveTo::reverse() const
{
    CCASSERT(false, "CCBezierTo doesn't support the 'reverse' method");
    return nullptr;
}

static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a +
            3*t*(powf(1-t,2))*b +
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

static inline float calcDeltaTime(float absAngle) {
    float k = (absAngle + 180) / 180;
    return k;
}

void MyBizeierMoveTo::update(float time)
{
    if (_target)
    {
        
        if (_isCommon)
        _prevTime = time - _prevTime;
        
        float xa = 0;
        float xb = _config.controlPoint_1.x;
        float xc = _config.controlPoint_2.x;
        float xd = _config.endPosition.x;
        
        float ya = 0;
        float yb = _config.controlPoint_1.y;
        float yc = _config.controlPoint_2.y;
        float yd = _config.endPosition.y;
        
        if (_isCommon)
            _myTime += _prevTime;
        
        
        float timeee = _isCommon ? _myTime : time;
        
        float x = bezierat(xa, xb, xc, xd, timeee);
        float y = bezierat(ya, yb, yc, yd, timeee);
        
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        Vec2 diff = currentPos - _previousPosition;
        _startPosition = _startPosition + diff;
        
        Vec2 newPos = _startPosition + Vec2(x,y);
        
        
        float angle = _isCommon ? atan2(-newPos.y + currentPos.y, newPos.x - currentPos.x) * 180 / M_PI : 0;
        float absAngle = _isCommon ? abs(angle) : 0;
        CCLOG("----- %f, %f, time: %f", absAngle, angle, time);
        float deltaTime = _isCommon ? calcDeltaTime(angle): 0;
        
        _target->setPosition(newPos);
        _previousPosition = newPos;
        
        if (_isCommon) {
            _isCommon = !_isCommon;
            this->update(_myTime + deltaTime * _prevTime);
        } else {
            _isCommon = !_isCommon;
        }
        
#else
        _target->setPosition( _startPosition + Vec2(x,y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
    }
}