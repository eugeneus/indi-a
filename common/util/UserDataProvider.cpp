
#include "UserDataProvider.h"

UserDataProvider::UserDataProvider()
{
}

UserDataProvider::~UserDataProvider() {}

UserDataProvider* UserDataProvider::create()
{
    
    UserDataProvider *pRet = new UserDataProvider();
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

bool UserDataProvider::init()
{
    
    //UserDefaut::getInstance()->getIntegerForKey("");
    
    return true;
}

int UserDataProvider::getUserScore() {
    return UserDefault::getInstance()->getIntegerForKey("score");
}

void UserDataProvider::updateUserScore(int pScore) {
    UserDefault::getInstance()->setIntegerForKey("score", pScore);
    UserDefault::getInstance()->flush();
}
