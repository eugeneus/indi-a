
#ifndef __Blind_Chef__Stickers__
#define __Blind_Chef__Stickers__

#include "cocos2d.h"

class Dish;

class Stickers: public cocos2d::Layer {
public:
    static Stickers* create();
    
    bool init();
    
    void setupQueue(std::vector<Dish *> queue);
private:
    typedef cocos2d::Layer super;
    cocos2d::Sprite* _first;
    cocos2d::Sprite* _next1;
    cocos2d::Sprite* _next2;
    cocos2d::Sprite* _next3;
    cocos2d::Sprite* _last;
};

#endif /* defined(__Blind_Chef__Stickers__) */
