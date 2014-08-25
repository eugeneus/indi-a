
#ifndef __BlindChef__FacebookWrap__
#define __BlindChef__FacebookWrap__

#import "FacebookCallBack.h"

class FacebookWrap
{
public:
    void share(const std::string& msg, iOSBridge::Callbacks::FacebookCallBack* callback);
};

#endif /* defined(__BlindChef__FacebookWrap__) */
