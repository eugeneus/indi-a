
#ifndef __BlindChef__Pot__
#define __BlindChef__Pot__

#include "cocos2d.h"

class Pot: public cocos2d::Layer {
private:
    typedef cocos2d::Layer super;
    cocos2d::Sprite* front;
    cocos2d::Sprite* back;
public:
    static Pot* create();
    
    bool init();
    cocos2d::Sprite* getFront();
    cocos2d::Sprite* getBack();
};

#endif /* defined(__BlindChef__Pot__) */
