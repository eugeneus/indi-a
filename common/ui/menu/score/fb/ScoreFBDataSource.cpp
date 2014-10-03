#include "ScoreFBDataSource.h"
#include "ScoreDto.h"
#include "FBManager.h"
#include "UserScoreResult.h"
#include "ScoreUserEntity.h"

USING_NS_CC;

ScoreFBDataSource* ScoreFBDataSource::create()
{
    ScoreFBDataSource *pRet = new ScoreFBDataSource();
    if (pRet && pRet->init())
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

ScoreFBDataSource::ScoreFBDataSource() {}
ScoreFBDataSource::~ScoreFBDataSource() {}

bool ScoreFBDataSource::init() {
    return true;
}

void ScoreFBDataSource::requestData() {
    SEL_CallFuncO func1 = callfuncO_selector(ScoreFBDataSource::onScoresReceived0);
    NotificationCenter::getInstance()->addObserver(this, func1, "score_complete", nullptr);
    
    SEL_CallFuncO func2 = callfuncO_selector(ScoreFBDataSource::onScoresReceived0);
    NotificationCenter::getInstance()->addObserver(this, func2, "score_error", nullptr);
    
    [FBManager getScoreList];
}

void ScoreFBDataSource::onScoresReceived(std::vector<GKScoreCpp> scores) {
   
}

void ScoreFBDataSource::onScoresReceived0(Ref *pSender) {
    CCLOG("sdfdsf");
    cocos2d::Vector<Ref *> data;
    
    if (pSender != nullptr) {
        UserScoreResult *result = (UserScoreResult *) pSender;
        cocos2d::Vector<ScoreUserEntity *> userData = result->getData();
        for (ScoreUserEntity *user : userData) {
            data.pushBack(user);
        }
    }
    
    _data.pushBack(data);
    //SlidingDataSourceCallback *callbakc = super::getCallback();
    //callbakc->requestDataComplete();
    NotificationCenter::getInstance()->postNotification("table_score_complete", pSender);
   // super::dataRequestComplete(data);
}

void ScoreFBDataSource::onScoresReceived1() {
    CCLOG("sdfdsf");
}
