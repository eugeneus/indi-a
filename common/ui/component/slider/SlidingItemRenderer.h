
#ifndef __BlindChef__SlidingItemRenderer__
#define __BlindChef__SlidingItemRenderer__

#include "cocos2d.h"

USING_NS_CC;

class SlidingItemRenderer : public cocos2d::Ref
{
private:
    
public:
    SlidingItemRenderer();
    virtual ~SlidingItemRenderer();

    virtual Layer* create(Ref* data) = 0;
};

#endif /* defined(__BlindChef__SlidingItemRenderer__) */
