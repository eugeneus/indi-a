
#ifndef __BlindChef__FBHWrapperCpp__
#define __BlindChef__FBHWrapperCpp__

#include <iostream>
#include <vector>
#include "GKCppAlternatives.h"

class FBHDelegate;
class ScoreRequestDelegate;


class FBHWrapperCpp {
    
public:
    
    FBHWrapperCpp();
    
    void retrieveTopTenAllTimeGlobalScores(std::string catagory);
    void setDelegate(FBHDelegate* gkhDelegate);
    void onScoresReceived(std::vector<GKScoreCpp> scores);
};

#endif /* defined(__BlindChef__FBHWrapperCpp__) */
