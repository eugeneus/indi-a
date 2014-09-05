
#ifndef __BlindChef__Health__
#define __BlindChef__Health__

#include "cocos2d.h"

class Health : public cocos2d::Layer {
private:
    int count;
    cocos2d::Label* label;
public:
    Health();
    ~Health();
    static Health* create(int count);
    bool init(int count);
};

#endif /* defined(__BlindChef__Health__) */
