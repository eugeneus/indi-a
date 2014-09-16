
#ifndef __BlindChef__Health__
#define __BlindChef__Health__

#include "cocos2d.h"

class Health : public cocos2d::Layer {
private:
    int count;
    cocos2d::Label* label;
    float _dt;
    
protected:
    void checkLives();
public:
    Health();
    ~Health();
    static Health* create(int count);
    bool init(int count);
    void update(float dt);
};

#endif /* defined(__BlindChef__Health__) */
