

#include "ScoreRequestDelegate.h"
#include "GKCppAlternatives.h"


void ScoreRequestDelegate::onScoresReceived(std::vector<GKScoreCpp> scores) {
    
    if (_debug) {
        std::cout << "\nFBHDelegate onFriendsScoreReceived";
    }
    
    //if (_currentDataSource) {
        _currentDataSource.completeReadScores(scores);
   // }
}
