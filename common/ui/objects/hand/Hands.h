
#ifndef __BlindChef__Hands__
#define __BlindChef__Hands__

#include "cocos2d.h"
#include "Hand.h"


//TODO: obsoete

class Hands : public cocos2d::Layer {
private:
    typedef Layer super;
public:
    Hand *leftHand;
    Hand *rightHand;
    static Hands* create(float dist);
    
    bool init(float dist);
};

#endif /* defined(__BlindChef__Hands__) */
