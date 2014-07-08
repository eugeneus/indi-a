
#ifndef __BlindChef__MindCloudTips__
#define __BlindChef__MindCloudTips__

#include "cocos2d.h"
#include "TipsFadeble.h"

class MindCloudTips : public TipsFadeble {
private:
    typedef TipsFadeble super;
public:
    static MindCloudTips* create(const std::string& tipsLevelImgFrame);
    
    bool init(const std::string& tipsLevelImgFrame);
};

#endif /* defined(__BlindChef__MindCloudTips__) */
