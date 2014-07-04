

#ifndef __BlindChef__BonusMenu__
#define __BlindChef__BonusMenu__

#include "cocos2d.h"

class BonusMenu : public cocos2d::Layer {
public:
    static BonusMenu* create();
    
    bool init();
    
    void bonus1Callback(cocos2d::Ref* pSender);
    void bonus2Callback(cocos2d::Ref* pSender);
    void bonus3Callback(cocos2d::Ref* pSender);
};

#endif /* defined(__BlindChef__BonusMenu__) */
