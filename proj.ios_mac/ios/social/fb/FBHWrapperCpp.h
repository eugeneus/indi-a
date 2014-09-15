
#ifndef __BlindChef__FBHWrapperCpp__
#define __BlindChef__FBHWrapperCpp__

#include <iostream>
#include <vector>
#include "GKCppAlternatives.h"

class FBHDelegate;


class FBHWrapperCpp {
    
public:
    
    FBHWrapperCpp();
    
    void retrieveTopTenAllTimeGlobalScores(std::string catagory);
    void setDelegate(FBHDelegate* gkhDelegate);
    
};

#endif /* defined(__BlindChef__FBHWrapperCpp__) */
