
#ifndef __BlindChef__ImageLabelMenuItem__
#define __BlindChef__ImageLabelMenuItem__

#include "cocos2d.h"

class ImageLabelMenuItem : public cocos2d::MenuItemSprite {
private:
    cocos2d::MenuItemSprite* item;
    cocos2d::Label* label;
public:
    static ImageLabelMenuItem* create(const std::string& text, const std::string& imageFrameName, const cocos2d::ccMenuCallback& callback);
    
    bool init(const std::string& text, const std::string& imageFrameName, const cocos2d::ccMenuCallback& callback);
    void changeLabelText(const std::string& text);
};

#endif /* defined(__BlindChef__ImageLabelMenuItem__) */
