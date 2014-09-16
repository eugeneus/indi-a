
#ifndef __BlindChef__ScoreRequestDelegate__
#define __BlindChef__ScoreRequestDelegate__

#include <iostream>
#include <vector>
#include <map>
#include "ScoreDataSource.h"

//forward declare structs
struct GKPlayerCpp;
struct GKScoreCpp;
struct GKAchievementCpp;

class ScoreRequestDelegate {
private:
    ScoreRequestDelegate(){};
    ScoreRequestDelegate(const ScoreRequestDelegate& other){};
    
public:
    ScoreDataSource _currentDataSource;
    static ScoreRequestDelegate& getInstance()
    {
        static ScoreRequestDelegate    instance; // Guaranteed to be destroyed.
        return instance;
    }
    
    bool _debug;
    void setDebug(bool debug){_debug = debug;};
    
    void onScoresReceived(std::vector<GKScoreCpp> scores);
};


#endif /* defined(__BlindChef__ScoreRequestDelegate__) */
