
#ifndef __BlindChef__Chef__
#define __BlindChef__Chef__

#include "cocos2d.h"
#include "Spritable.h"

class Chef : public cocos2d::Ref {
public:
   Chef();
   ~Chef();
    static Chef* create(cocos2d::Layer* aLayer);
    //static cocos2d::Scene* createScene();
    
    bool init(cocos2d::Layer* aLayer);
 
   void setScale(float aScaleFactor);
   cocos2d::Size getSize();
   void setOrigin(cocos2d::Point anOrigin);

private:
   typedef cocos2d::Ref super;
   cocos2d::Rect _chefRect;
   cocos2d::Rect _leftHandRect;
   cocos2d::Rect _rightHandRect;
   cocos2d::Layer* _layer;
   cocos2d::Sprite* _chef;
   cocos2d::Sprite* _leftHand;
   cocos2d::Sprite* _rightHand;
};

#endif /* defined(__BlindChef__Chef__) */
