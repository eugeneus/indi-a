
#ifndef __BlindChef__FacebookShare__
#define __BlindChef__FacebookShare__

#include "cocos2d.h"

class FacebookShare
{
public:
    static const int SESSION_STATE_CLOSED = 0;
    static const int SESSION_STATE_CLOSEDLOGINFAILED = 1;
    static const int SESSION_STATE_CREATED = 2;
    static const int SESSION_STATE_CREATEDOPENING = 3;
    static const int SESSION_STATE_CREATEDTOKENLOADED = 4;
    static const int SESSION_STATE_OPEN = 5;
    static const int SESSION_STATE_OPENTOKENEXTENDED = 6;
    
    //Instance using lazy initialization
    static FacebookShare& sharedFacebookShare()
    {
        static FacebookShare instance;
        return instance;
    }
    
    //Destructor
    ~FacebookShare();
    
    //Session
    void createSession();
    
    void openSession(cocos2d::Ref* target, cocos2d::SEL_CallFunc callback);
    void openSessionCallback();
    
    void closeSession();
    void closeSessionAndClearTokenInformation();
    
    bool isSessionOpen();
    
    /* Session state implementation is currently useless, kana? */
    void setSessionState(int state);
    int getSessionState();
    
    //Method for posting
    void post(const char* text, cocos2d::Ref* target, cocos2d::SEL_CallFunc callback);
    void postCallback();
    
    void setIsPostSuccess(bool success);
    bool isPostSuccess();
private:
    //Session
    int mSessionState;
    
    //Session callback
    cocos2d::Ref* lTarget;
    cocos2d::SEL_CallFunc lCallback;
    
    //Post
    bool isPostSucces;
    
    //Post callback
    cocos2d::Ref* pTarget;
    cocos2d::SEL_CallFunc pCallback;
    
    //Hidden constructor
    FacebookShare();
};


#endif /* defined(__BlindChef__FacebookShare__) */
