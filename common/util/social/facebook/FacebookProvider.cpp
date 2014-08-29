
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

void FacebookProvider::share(const std::string msg)
{
    // запрос продуктов
    FacebookWrap* wrap = new FacebookWrap::FacebookWrap();
    wrap->share(msg, this); //передаем указатель на себя для Callback вызовов своих методов.
    delete wrap;
}

void FacebookProvider::complete() {
    //
    CCLOG("..fb.. complete..");
}

void FacebookProvider::readGloabalScore() {
    FacebookWrap* wrap = new FacebookWrap::FacebookWrap();
    wrap->readGlobalScores(this);
}