
#ifndef __BlindChef__ScoreLayer__
#define __BlindChef__ScoreLayer__

#include "cocos2d.h"

class ScoreLayer : public cocos2d::Layer {
    
private:
    int score;
    cocos2d::Label* scoreLabel;
protected:
    bool init(int score);
    void update(float dt);
public:
    ScoreLayer();
    virtual ~ScoreLayer();
    
    static ScoreLayer* create(int score);
    
    void updateScore(int dt);
};

#endif /* defined(__BlindChef__ScoreLayer__) */
