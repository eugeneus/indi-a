
#ifndef __BlindChef__Pot__
#define __BlindChef__Pot__

#include "cocos2d.h"

class Pot: public cocos2d::Layer {
private:
    cocos2d::Sprite* front;
    cocos2d::Sprite* back;
public:
    static Pot* create();
    
    bool init();
};

#endif /* defined(__BlindChef__Pot__) */
