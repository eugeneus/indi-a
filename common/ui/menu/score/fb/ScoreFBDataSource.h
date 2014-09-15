
#ifndef __BlindChef__ScoreFBDataSource__
#define __BlindChef__ScoreFBDataSource__

#include "cocos2d.h"
#include "SlidingDataSource.h"
#include "FBHDelegate.h"
#include "FBHWrapperCpp.h"

USING_NS_CC;

class ScoreFBDataSource : public SlidingDataSource, public FBHDelegate
{
private:
    FBHWrapperCpp* _dataProvider;
protected:
    
public:
    
    static ScoreFBDataSource* create();
    virtual bool init();
    ScoreFBDataSource();
    ScoreFBDataSource(const ScoreFBDataSource& other);
    virtual ~ScoreFBDataSource();
    FBHDelegate* copy();
    
    void requestData();
    virtual void onScoresReceived(std::vector<GKScoreCpp> scores);
};

#endif /* defined(__BlindChef__ScoreFBDataSource__) */
