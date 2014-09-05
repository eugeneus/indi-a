
#ifndef __BlindChef__FacebookCallBack__
#define __BlindChef__FacebookCallBack__

#include "cocos2d.h"

using namespace cocos2d;

namespace iOSBridge
{
    namespace Callbacks
    {
        
        enum
        {
            kFBCallbackGlobalScore = 0,
            kFBCallbackPostScore  // 1
            
        } typedef FBCallbackType;
        
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
            FBCallbackType type = FBCallbackType::kFBCallbackGlobalScore;
            virtual void completeReadScores(std::vector<FacebookScore *> score) = 0;
            virtual void error() = 0;
        };
        
        class FacebookLoginCallBack
        {
        public:
            virtual void complete() = 0;
            virtual void error() = 0;
            virtual void canceled() = 0;
        };
    };
};

#endif /* defined(__BlindChef__FacebookCallBack__) */
