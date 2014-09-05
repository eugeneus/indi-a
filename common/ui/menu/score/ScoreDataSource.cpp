
#include "ScoreDataSource.h"

USING_NS_CC;

ScoreDataSource* ScoreDataSource::create(FacebookProvider* provider)
{
    ScoreDataSource *pRet = new ScoreDataSource();
    if (pRet && pRet->init(provider))
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


bool ScoreDataSource::init(FacebookProvider* provider) {
    _dataProvider = provider;
    return true;
}

void ScoreDataSource::requestData() {
    _dataProvider->readGloabalScore(this);
}

void ScoreDataSource::completeReadScores(std::vector<iOSBridge::Callbacks::FacebookScore *> score) {
    std::vector<Ref *> data;
    for (iOSBridge::Callbacks::FacebookScore *sc : score) {
        data.push_back(ScoreDto::create(sc->name, sc->photo, sc->score));
    }
    
    this->dataRequestComplete(data);
}

void ScoreDataSource::error() {
    std::vector<Ref *> data;
    this->dataRequestComplete(data);
}

