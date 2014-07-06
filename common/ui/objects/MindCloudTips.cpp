
#include "MindCloudTips.h"

USING_NS_CC;

MindCloudTips* MindCloudTips::create(const std::string& tipsLevelImgFrame)
{
    MindCloudTips *pRet = new MindCloudTips();
    if (pRet && pRet->init(tipsLevelImgFrame))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool MindCloudTips::init(const std::string& tipsLevelImgFrame)
{
    if ( !super::init("tips.png", tipsLevelImgFrame) )
    {
        return false;
    }
    
    return true;
}