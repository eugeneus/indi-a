
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
    wrap = new FacebookWrap::FacebookWrap();
    return true;
}

void FacebookProvider::share(const std::string msg, iOSBridge::Callbacks::FacebookCallBack* callback)
{
    // запрос продуктов
    FacebookWrap* wrap = new FacebookWrap::FacebookWrap();
    wrap->share(msg, callback); //передаем указатель на себя для Callback вызовов своих методов.
    delete wrap;
}


void FacebookProvider::readGloabalScore(iOSBridge::Callbacks::FacebookCallBack* callback) {
    _currCallback = callback;
    
    //wrap->readGlobalScores(callback);
    
    if (wrap->login(this)) {
        
    }
}


///////////////// FBLoginCallback


void FacebookProvider::complete() {
    iOSBridge::Callbacks::FBCallbackType type = _currCallback->type;
    switch(type)
    {
        case iOSBridge::Callbacks::kFBCallbackGlobalScore:
        {
            wrap->readGlobalScores(_currCallback);
            break;
        }
        case iOSBridge::Callbacks::kFBCallbackPostScore: {
            wrap->postScore(1010, _currCallback);
            //item = GarbageFactory::createGarbage(sub_item_type);
            break;
        }
            
        default:
        {
            _currCallback->error();
        }
    }
}

void FacebookProvider::error() {
    _currCallback->error();
}

void FacebookProvider::canceled() {
    _currCallback->error();
}