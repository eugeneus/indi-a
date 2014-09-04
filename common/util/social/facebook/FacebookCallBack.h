
#ifndef __BlindChef__FacebookCallBack__
#define __BlindChef__FacebookCallBack__

#include "cocos2d.h"

using namespace cocos2d;

namespace iOSBridge
{
    namespace Callbacks
    {
        class FacebookScore : public Ref
        {
        public:
            std::string uid;
            std::string name;
            int score;
            std::string photo;
            float price;
        };
        
        class FacebookCallBack
        {
        public:
            virtual void completeReadScores(std::vector<FacebookScore *> score) = 0;
            virtual void error() = 0;
        };
    };
};

#endif /* defined(__BlindChef__FacebookCallBack__) */
