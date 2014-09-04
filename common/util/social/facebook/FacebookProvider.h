
#ifndef __BlindChef__FacebookProvider__
#define __BlindChef__FacebookProvider__

#include "cocos2d.h"
#include "FacebookCallBack.h"
#include "FacebookWrap.h"
#include "ScoreDto.h"

class FacebookProvider : public cocos2d::Ref///, public iOSBridge::Callbacks::FacebookCallBack
{
public:
    FacebookProvider();
    ~FacebookProvider();
    static FacebookProvider* create();
    void share(std::string msg, iOSBridge::Callbacks::FacebookCallBack* callback);
    std::vector<ScoreDto *> readGloabalScore(iOSBridge::Callbacks::FacebookCallBack* callback);
    //void completeReadScores(std::vector<iOSBridge::Callbacks::FacebookScore *> score);
private:
    bool init();
};

#endif /* defined(__BlindChef__FacebookProvider__) */
