
#ifndef __BlindChef__UserScoreResult__
#define __BlindChef__UserScoreResult__

#include "cocos2d.h"
#include "ScoreUserEntity.h"

class UserScoreResult : public cocos2d::Ref {
private:
    cocos2d::Vector<ScoreUserEntity *> _data;
public:
    UserScoreResult() {};
    virtual ~UserScoreResult() {};
    
    static UserScoreResult* create();
    bool init();
    
    cocos2d::Vector<ScoreUserEntity *> getData();
    void addData(cocos2d::Vector<ScoreUserEntity *> pData);
    void addData(ScoreUserEntity *pData);
};

#endif /* defined(__BlindChef__UserScoreResult__) */
