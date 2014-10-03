
#include "UserScoreResult.h"
USING_NS_CC;

UserScoreResult* UserScoreResult::create() {
    UserScoreResult *pRet = new UserScoreResult();
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

bool UserScoreResult::init() {
    
    return true;
}

cocos2d::Vector<ScoreUserEntity *> UserScoreResult::getData() {
    return _data;
}

void UserScoreResult::addData(cocos2d::Vector<ScoreUserEntity *> pData) {
    _data.pushBack(pData);
}

void UserScoreResult::addData(ScoreUserEntity *pData) {
    _data.pushBack(pData);
}