
#ifndef __BlindChef__ScoreLBDataSource__
#define __BlindChef__ScoreLBDataSource__

#include "cocos2d.h"
#include "SlidingDataSource.h"
#include "GKHDelegate.h"
#include "GKHWrapperCpp.h"

USING_NS_CC;

class ScoreLBDataSource : public SlidingDataSource, public GKHDelegate
{
private:
   GKHWrapperCpp* _dataProvider;
protected:
    
public:
    
    static ScoreLBDataSource* create();
    virtual bool init();
    ScoreLBDataSource();
    virtual ~ScoreLBDataSource();
    
    void requestData();
    virtual void onScoresReceived(std::vector<GKScoreCpp> scores);
};

#endif /* defined(__BlindChef__ScoreLBDataSource__) */
