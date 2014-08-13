

#ifndef __BlindChef__BonusMenu__
#define __BlindChef__BonusMenu__

#include "cocos2d.h"
class ImageLabelMenuItem;

enum
{
    kBonusType1 = 0,
    kBonusType2,
    kBonusType3
};

class BonusMenu : public cocos2d::Layer {
private:
    cocos2d::Value bonus1Count;
    cocos2d::Value bonus2Count;
    cocos2d::Value bonus3Count;
    ImageLabelMenuItem* bonus1;
    ImageLabelMenuItem* bonus2;
    ImageLabelMenuItem* bonus3;
  
    void updateBonus(cocos2d::Value& bonusCount, int delta, ImageLabelMenuItem* bonusLabel);
    
public:
    static BonusMenu* create();
    
    bool init();
    
    void bonus1Callback(cocos2d::Ref* pSender);
    void bonus2Callback(cocos2d::Ref* pSender);
    void bonus3Callback(cocos2d::Ref* pSender);
    
    void changeBonusCount(int bonus_type, bool incr);
};

#endif /* defined(__BlindChef__BonusMenu__) */
