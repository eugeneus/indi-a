
#ifndef __BlindChef__BaseGamePopup__
#define __BlindChef__BaseGamePopup__


#include "cocos2d.h"
#include "ButtonConstants.h"

class BaseGamePopup : public cocos2d::Layer
{
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
    void initItem(cocos2d::Vector<cocos2d::MenuItem*>& menuItems, const std::string& spriteFrameName, const cocos2d::ccMenuCallback& callback);
    void changeScene(cocos2d::Scene* newScene);
    void addLabel(cocos2d::Node* target, const cocos2d::TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color, float posX, float posY, int tag);
    cocos2d::Label* createLabel(const cocos2d::TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color);
    void addLabelsLine(cocos2d::Node* target, cocos2d::Label* label1, cocos2d::Label* label2, float posX, float posY);
public:
   // BaseGamePopup();
   // virtual ~BaseGamePopup();
    virtual bool init();
};

#endif /* defined(__BlindChef__BaseGamePopup__) */
