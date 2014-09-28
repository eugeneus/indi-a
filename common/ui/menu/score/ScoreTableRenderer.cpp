
#include "ScoreTableRenderer.h"
#include "ScoreUserEntity.h"

USING_NS_CC;

ScoreTableRenderer* ScoreTableRenderer::create()
{
    ScoreTableRenderer *pRet = new ScoreTableRenderer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

ScoreTableRenderer::ScoreTableRenderer() {}
ScoreTableRenderer::~ScoreTableRenderer() {}

bool ScoreTableRenderer::init() {
    return true;
}

Label* createLabel(std::string text, TTFConfig ttf, Color3B color) {
    Label* label = Label::createWithTTF(ttf, text);
    label->setAnchorPoint(Vec2(0,0));
    label->setColor(color);
    
    return label;
}

Layer* ScoreTableRenderer::create(Ref* data) {
    if (!data) return Layer::create();
    
    ScoreUserEntity* dto = (ScoreUserEntity *) data;
    
    TTFConfig ttf32;
    ttf32.fontSize = 32;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorWhite = Color3B(255, 255, 255);
    
    Label* label = createLabel(dto->getName(), ttf32, colorWhite);
    
    Layer *result = Layer::create();
    result->addChild(label);
    return result;
}