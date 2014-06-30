
#ifndef __BlindChef__Cyclable__
#define __BlindChef__Cyclable__

#include "cocos2d.h"

class Cyclable : public cocos2d::Layer {
    
private:
    cocos2d::Vector<cocos2d::Sprite*> sprites;
    float endPoint;
    float cyclingSpeed;
protected:
    bool init(const char* bgSpriteFrameName, float speed, float length);
    void update(float dt);
public:
    Cyclable();
    virtual ~Cyclable();
    
    static Cyclable* create(const char* bgSpriteFrameName, float speed, float length);
    
    void stopCycling();
    void startCycling();
    void changeCyclingSpeed(float speed);
};

#endif /* defined(__BlindChef__Cyclable__) */
