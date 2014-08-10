
#ifndef __BlindChef__Multiplier__
#define __BlindChef__Multiplier__

#include "cocos2d.h"

class MultiplierIndicator;

class Multiplier : public cocos2d::Layer {
    
private:
    int _count;
    int _itemId;
    cocos2d::Label* _countLabel;
    cocos2d::Sprite* _countSprite;
    
    MultiplierIndicator* _ind;
protected:
    bool init();
    void updateLabel();
public:
    Multiplier();
    virtual ~Multiplier();
    
    static Multiplier* create();
    
    int update(int pItemId);
    void reset();
    int getCount();
};


#endif /* defined(__BlindChef__Multiplier__) */
