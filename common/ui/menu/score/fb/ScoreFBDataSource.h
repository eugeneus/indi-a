
#ifndef __BlindChef__ScoreFBDataSource__
#define __BlindChef__ScoreFBDataSource__

#include "cocos2d.h"
#include "SlidingDataSource.h"
#include "FBHDelegate.h"
#include "FBHWrapperCpp.h"

USING_NS_CC;

class ScoreFBDataSource : public SlidingDataSource
{
private:
    typedef SlidingDataSource super;
protected:
    
public:
    
    static ScoreFBDataSource* create();
    virtual bool init();
    ScoreFBDataSource();
    virtual ~ScoreFBDataSource();

    
    void requestData();
    virtual void onScoresReceived(std::vector<GKScoreCpp> scores);
    
    void onScoresReceived0(Ref *pSender);
    void onScoresReceived1();
};

#endif /* defined(__BlindChef__ScoreFBDataSource__) */
