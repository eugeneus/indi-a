

#ifndef __BlindChef__ScoreDataSource__
#define __BlindChef__ScoreDataSource__

#include "cocos2d.h"
#include "SlidingDataSource.h"
#include "FacebookProvider.h"
#include "FacebookCallBack.h"

USING_NS_CC;

class ScoreDataSource : public SlidingDataSource, public iOSBridge::Callbacks::FacebookCallBack
{
private:
    FacebookProvider* _dataProvider;
protected:
    
public:
    
    static ScoreDataSource* create(FacebookProvider* provider);
    virtual bool init(FacebookProvider* provider);
    ScoreDataSource();
    virtual ~ScoreDataSource();
    
    void requestData();
    
    void completeReadScores(std::vector<iOSBridge::Callbacks::FacebookScore *> score);
    void error();
};

#endif /* defined(__BlindChef__ScoreDataSource__) */
