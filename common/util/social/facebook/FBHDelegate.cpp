
#include "FBHDelegate.h"
#include "GKCppAlternatives.h"

FBHDelegate::FBHDelegate(){
    
    _debug = true;
    
}

FBHDelegate::FBHDelegate(const FBHDelegate& other) : _debug(other._debug), ii(1000) {
    std::cout << "\nFcopied";
}

void FBHDelegate::onScoresReceived(std::vector<GKScoreCpp> scores) {
    
    if (_debug) {
        std::cout << "\nFBHDelegate onFriendsScoreReceived";
    }
}
