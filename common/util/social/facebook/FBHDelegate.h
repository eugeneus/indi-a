
#ifndef __BlindChef__FBHDelegate__
#define __BlindChef__FBHDelegate__

#include <iostream>
#include <vector>
#include <map>

//forward declare structs
struct GKPlayerCpp;
struct GKScoreCpp;
struct GKAchievementCpp;

class FBHDelegate {
private:
    
    
public:
    int ii = 0;
    virtual FBHDelegate* copy() = 0;
    FBHDelegate();
    FBHDelegate(const FBHDelegate& other);
    bool _debug;
    void setDebug(bool debug){_debug = debug;};
    
    
    virtual void onScoresReceived(std::vector<GKScoreCpp> scores);
};

#endif /* defined(__BlindChef__FBHDelegate__) */
