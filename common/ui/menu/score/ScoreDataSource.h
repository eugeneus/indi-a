

#ifndef __BlindChef__ScoreDataSource__
#define __BlindChef__ScoreDataSource__

#include "cocos2d.h"
#include "SlidingDataSource.h"
#include "FBHWrapperCpp.h"
#include "GKCppAlternatives.h"

USING_NS_CC;

class ScoreDataSource : public SlidingDataSource
{
private:
    
protected:
    
public:
    
    static ScoreDataSource* create();
    virtual bool init();
    ScoreDataSource();
    virtual ~ScoreDataSource();
    
    void requestData();
    
    void completeReadScores(std::vector<GKScoreCpp> score);
    void error();
};

#endif /* defined(__BlindChef__ScoreDataSource__) */
