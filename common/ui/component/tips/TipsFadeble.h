
#ifndef __BlindChef__TipsFadeble__
#define __BlindChef__TipsFadeble__

#include "cocos2d.h"

class TipsFadeble : public cocos2d::Layer {
private:
    cocos2d::Sprite* bg;
    cocos2d::Sprite* img;
public:
    static TipsFadeble* create(const std::string& bgFrameName, const std::string& tipsImgFrameName);
    
    bool init(const std::string& bgFrameName, const std::string& tipsImgFrameName);
    
    void showTip();
    void hideTip();
    void toggleTip();
    void changeTip(const std::string& tipsImgFrameName);
};

#endif /* defined(__BlindChef__TipsFadeble__) */
