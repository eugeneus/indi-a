
#ifndef __BlindChef__FacebookCallBack__
#define __BlindChef__FacebookCallBack__

#include "cocos2d.h"

using namespace cocos2d;

namespace iOSBridge
{
    namespace Callbacks
    {
        class IAPItem : public Ref
        {
        public:
            std::string identification;
            std::string name;
            std::string localizedTitle;
            std::string localizedDescription;
            float price;
        };
        
        class FacebookCallBack
        {
        public:
            virtual void complete() = 0;
        };
    };
};

#endif /* defined(__BlindChef__FacebookCallBack__) */
