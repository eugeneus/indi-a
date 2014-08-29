
#ifndef __BlindChef__FacebookProvider__
#define __BlindChef__FacebookProvider__

#include "cocos2d.h"
#include "FacebookCallBack.h"
#include "FacebookWrap.h"

class FacebookProvider : public cocos2d::Ref, public iOSBridge::Callbacks::FacebookCallBack
{
public:
    FacebookProvider();
    ~FacebookProvider();
    static FacebookProvider* create();
    void share(std::string msg);
    void readGloabalScore();
    void complete();
private:
    bool init();
};

#endif /* defined(__BlindChef__FacebookProvider__) */
