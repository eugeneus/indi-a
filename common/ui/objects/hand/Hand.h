
#ifndef __BlindChef__Hand__
#define __BlindChef__Hand__

#include "cocos2d.h"

class Hand : public cocos2d::Layer {
private:
    typedef Layer super;
    cocos2d::Sprite* handImg;
public:
    static Hand* create();
    
    bool init();
    
    void mirrorImg();
};

#endif /* defined(__BlindChef__Hand__) */
