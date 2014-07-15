
#ifndef __BlindChef__Cyclable__
#define __BlindChef__Cyclable__

#include "cocos2d.h"

class Cyclable : public cocos2d::LayerColor {
    
private:
    typedef  cocos2d::LayerColor super;
    cocos2d::Vector<cocos2d::Sprite*> sprites;
    cocos2d::Vector<cocos2d::Node*> children;
    float endPoint;
    float cyclingSpeed;
    float actionDuration;
   float actionLength;
protected:
    bool init(const char* bgSpriteFrameName, float speed, float length);
    
public:
    Cyclable();
    virtual ~Cyclable();
    
    static Cyclable* create(const char* bgSpriteFrameName, float speed, float length);
    
    void stopCycling();
    void startCycling();
    void changeCyclingSpeed(float speed);
    
    virtual void addChild(cocos2d::Node* node, int zIndex);
    cocos2d::Vector<cocos2d::Node*> getChildrenItems();
};

#endif /* defined(__BlindChef__Cyclable__) */
