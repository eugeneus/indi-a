#include "ScoreFBDataSource.h"
#include "ScoreDto.h"

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

ScoreFBDataSource::ScoreFBDataSource(const ScoreFBDataSource& other) : SlidingDataSource(other), FBHDelegate(other), _dataProvider(other._dataProvider) {
    CCLOG("............ jopaaa copied");
    std::cout << "\n........bab.ab.ab.a.b.ab....b.a.ba.b.ab..";
}

bool ScoreFBDataSource::init() {
    _dataProvider = new FBHWrapperCpp();
    _dataProvider->setDelegate(this);
    return true;
}

void ScoreFBDataSource::requestData() {
    
    _dataProvider->retrieveTopTenAllTimeGlobalScores("fsdfsdf");
}

void ScoreFBDataSource::onScoresReceived(std::vector<GKScoreCpp> scores) {
    std::vector<Ref *> data;
    for (GKScoreCpp sc : scores) {
        data.push_back(ScoreDto::create(sc.playerID, sc.formattedValue, sc.rank));
    }
    
    this->dataRequestComplete(data);
}

FBHDelegate* ScoreFBDataSource::copy() {
    return new ScoreFBDataSource(*this);
}