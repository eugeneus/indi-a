
#ifndef __BlindChef__Pot__
#define __BlindChef__Pot__

#include "cocos2d.h"

class Pot: public cocos2d::LayerColor {
public:
    static Pot* create(cocos2d::Layer* aGameLayer, int aFrontZO, int aBackZO);
    
    bool init(cocos2d::Layer* aGameLayer, int aFrontZO, int aBackZO);
    cocos2d::Sprite* getFront();
    cocos2d::Sprite* getBack();
   cocos2d::Rect getFrontRect();
   cocos2d::Rect getBackRect();
   void setOriginPos(cocos2d::Point anOrigin);
private:
   typedef cocos2d::Layer super;
   cocos2d::Sprite* _front;
   cocos2d::Sprite* _back;
};

#endif /* defined(__BlindChef__Pot__) */
