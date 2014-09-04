

#ifndef __BlindChef__ScoreTableRenderer__
#define __BlindChef__ScoreTableRenderer__

#include "cocos2d.h"
#include "SlidingItemRenderer.h"

USING_NS_CC;

class ScoreTableRenderer : public SlidingItemRenderer
{
private:
    
public:
    
    static ScoreTableRenderer* create();
    virtual bool init();
    ScoreTableRenderer();
    virtual ~ScoreTableRenderer();
    
    virtual Layer* create(Ref* data);
};

#endif /* defined(__BlindChef__ScoreTableRenderer__) */
