
#include "ScoreLBDataSource.h"
#include "ScoreDto.h"

USING_NS_CC;

ScoreLBDataSource* ScoreLBDataSource::create()
{
    ScoreLBDataSource *pRet = new ScoreLBDataSource();
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

ScoreLBDataSource::ScoreLBDataSource() {}
ScoreLBDataSource::~ScoreLBDataSource() {}

bool ScoreLBDataSource::init() {
    _dataProvider = new GKHWrapperCpp();
    _dataProvider->setDelegate(this);
    return true;
}

void ScoreLBDataSource::requestData() {
    
    _dataProvider->retrieveTopTenAllTimeGlobalScores("fsdfsdf");
}

void ScoreLBDataSource::onScoresReceived(std::vector<GKScoreCpp> scores) {
    std::vector<Ref *> data;
    for (GKScoreCpp sc : scores) {
        data.push_back(ScoreDto::create(sc.playerID, sc.formattedValue, sc.rank));
    }
    
    this->dataRequestComplete(data);
}