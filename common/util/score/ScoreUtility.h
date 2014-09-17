
#ifndef __BlindChef__ScoreUtility__
#define __BlindChef__ScoreUtility__

#include "cocos2d.h"

class ScoreUtility {
public:
    static void showLeaderboard();
    static void submitScore();
    static bool isLeaderboardAvailable();
};

#endif /* defined(__BlindChef__ScoreUtility__) */
