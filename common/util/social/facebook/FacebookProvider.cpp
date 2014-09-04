
#include "FacebookProvider.h"

FacebookProvider::FacebookProvider()
{
    
}

FacebookProvider::~FacebookProvider() {}

FacebookProvider* FacebookProvider::create()
{
    
    FacebookProvider *pRet = new FacebookProvider();
    if (pRet && pRet->init())
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool FacebookProvider::init()
{
    
    return true;
}

void FacebookProvider::share(const std::string msg, iOSBridge::Callbacks::FacebookCallBack* callback)
{
    // запрос продуктов
    FacebookWrap* wrap = new FacebookWrap::FacebookWrap();
    wrap->share(msg, callback); //передаем указатель на себя для Callback вызовов своих методов.
    delete wrap;
}


std::vector<ScoreDto *> FacebookProvider::readGloabalScore(iOSBridge::Callbacks::FacebookCallBack* callback) {
    std::vector<ScoreDto *> scores;
    
    FacebookWrap* wrap = new FacebookWrap::FacebookWrap();
    wrap->readGlobalScores(callback);
    
    return scores;
}