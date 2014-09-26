
#include "Health.h"
#include "UserDataProvider.h"
#include "SoundsConstants.h"

USING_NS_CC;

Health::Health() {}
Health::~Health() {}

Health* Health::create(int pCount) {
    Health *pRet = new Health();
    
    if (pRet && pRet->init(pCount))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool Health::init(int pCount) {
    if (!Layer::init()) {
        return false;
    }
    
    count = pCount;
   
    Sprite* health = Sprite::createWithSpriteFrameName("health.png");
    health->setPosition(Vec2(health->getPosition().x + 40, health->getPosition().y - 40 - health->getContentSize().height/2));
    this->addChild(health);
    
    TTFConfig ttf32;
    ttf32.fontSize = 32;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorYellow = Color3B(255, 240, 104);
    label = Label::createWithTTF(ttf32, CCString::createWithFormat("x%i", count)->getCString());
    //label->setAnchorPoint(Vec2(0,40));
    label->setPosition(Vec2(health->getPosition().x + health->getContentSize().width, health->getPosition().y));
    label->setColor(colorYellow);
    this->addChild(label);
    
    this->checkLives();
    
    _dt = 0;
    this->scheduleUpdate();
    
    return true;
}

static inline long millisecondNow()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void Health::update(float dt) {
    _dt += dt;
    //if (_dt > 60) {
        _dt = 0;
        this->checkLives();
   // }
}

void Health::checkLives() {
    int livesCount = UserDataProvider::getInstance()->getUserLives();
    if (livesCount < 10) {
        long now = millisecondNow();
       // for (int i=livesCount + 1; i < 10 + 1; i ++) {
            std::string timeout = UserDataProvider::getInstance()->getLiveTimeout(0);
            long t = atol(timeout.c_str());
            if (t != 0 && now - t > 10 * 60 * 1000) { // 10 min
                int count = (int)round ((now - t) / 10.0 * 60 * 1000);
                if (count < 0 || count == 0) count = 1;
                livesCount += count;
                if (livesCount > 10) livesCount = 10;
                UserDataProvider::getInstance()->updateLiveTimeout(0, CCString::createWithFormat("%li", now)->getCString());
                UserDataProvider::getInstance()->updateUserLives(livesCount);
                count = livesCount;
                label->setString(CCString::createWithFormat("x%i", count)->getCString());
                
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BONUS_PICKUP);
            }
       // }
    }
}