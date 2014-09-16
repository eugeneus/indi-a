
#include "ScoreDataSource.h"
#include "ScoreDto.h"
#include "ScoreRequestDelegate.h"

USING_NS_CC;

ScoreDataSource* ScoreDataSource::create()
{
    ScoreDataSource *pRet = new ScoreDataSource();
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

ScoreDataSource::ScoreDataSource() {}
ScoreDataSource::~ScoreDataSource() {}
ScoreDataSource::ScoreDataSource(ScoreDataSource const& copy):_dataProvider(copy._dataProvider) {}


bool ScoreDataSource::init() {
    _dataProvider = new FBHWrapperCpp();
    ScoreRequestDelegate::getInstance()._currentDataSource = *this;
    _dataProvider->setDelegate(nullptr);
    return true;
}

void ScoreDataSource::requestData() {
    _dataProvider->retrieveTopTenAllTimeGlobalScores("");
}

void ScoreDataSource::completeReadScores(std::vector<GKScoreCpp> score) {
    std::vector<Ref *> data;
    for (GKScoreCpp sc : score) {
        data.push_back(ScoreDto::create(sc.playerID, sc.formattedValue, sc.rank));
    }
    
    this->dataRequestComplete(data);
}

void ScoreDataSource::error() {
    std::vector<Ref *> data;
    this->dataRequestComplete(data);
}

