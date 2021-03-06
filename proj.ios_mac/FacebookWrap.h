
#ifndef __BlindChef__FacebookWrap__
#define __BlindChef__FacebookWrap__

#import "FacebookCallBack.h"

class FacebookWrap
{
private:
    
public:
    __block iOSBridge::Callbacks::FacebookCallBack* _callback;
    std::string str;
    
    FacebookWrap();
    ~FacebookWrap();
    
    bool login(iOSBridge::Callbacks::FacebookLoginCallBack* callback);
    
    void share(const std::string& msg, iOSBridge::Callbacks::FacebookCallBack* callback);
    void doShare(const std::string& msg);
    
    void postScore(int score, iOSBridge::Callbacks::FacebookCallBack* callback);
    void doPostScore(int score);
    
    void readGlobalScores(iOSBridge::Callbacks::FacebookCallBack* callback);
    void doReadGlobalScores(iOSBridge::Callbacks::FacebookCallBack* callback);
    void readGlobalScoreComplete();
    
    bool initSession();
    //void sessionStateChanged(FBSession *session, FBSessionState state, NSError *error);
};

#endif /* defined(__BlindChef__FacebookWrap__) */
