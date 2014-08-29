
#ifndef __BlindChef__GameCycleIndicator__
#define __BlindChef__GameCycleIndicator__

#include "cocos2d.h"
#include "BaseIndicator.h"

class GameCycleIndicator : public BaseIndicator {
private:
    typedef BaseIndicator super;
    float _gameTime;
    float _currentTime = 0;
public:
    GameCycleIndicator();
    virtual ~GameCycleIndicator();
    static GameCycleIndicator* createWithGameTime(float gameTime);
    
    bool initWithGameTime(float gemaTimes);
    
    void nextStep(float dt);
    void prevStep(float dt);
    
    virtual void restart();
    void setGameTime(float gt);
};

#endif /* defined(__BlindChef__GameCycleIndicator__) */
