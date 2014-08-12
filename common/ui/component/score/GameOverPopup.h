
#ifndef __BlindChef__GameOverPopup__
#define __BlindChef__GameOverPopup__

#include "cocos2d.h"
#include "BaseGamePopup.h"

class GameOverPopup : public BaseGamePopup
{
private:
    typedef BaseGamePopup super;
protected:
    virtual void initMenuItems(cocos2d::Vector<cocos2d::MenuItem*>& menuItems);
public:
    GameOverPopup();
    virtual ~GameOverPopup();
    
    virtual bool init();
    
    static GameOverPopup* create();
    
    void menuMainMenu(cocos2d::Ref* pSender);
    void menuStoreMenu(cocos2d::Ref* pSender);
    void playAgainMenu(cocos2d::Ref* pSender);
    cocos2d::Label* createLabel(const cocos2d::TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color);
    void addLabelsLine(cocos2d::Node* target, cocos2d::Label* label1, cocos2d::Label* label2, float posX, float posY);
    void addLabel(cocos2d::Node* target, const cocos2d::TTFConfig& ttfConfig, const std::string& text, const cocos2d::Color3B& color, float posX, float posY);
    
    cocos2d::Node* createScoreLabel();
};

#endif /* defined(__BlindChef__GameOverPopup__) */
