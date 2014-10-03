
#ifndef __BlindChef__ScoreUserEntity__
#define __BlindChef__ScoreUserEntity__

#include "cocos2d.h"

class ScoreUserEntity : public cocos2d::Ref {
private:
    std::string _name;
    std::string _imageUrl;
    int _score;
public:
    ScoreUserEntity() {};
    ~ScoreUserEntity() {};
    
    static ScoreUserEntity* create(std::string pName, std::string pImageUrl, int score);
    bool init(std::string pName, std::string pImageUrl, int score);
    
    std::string getName();
    std::string getImageUrl();
    int getScore();
};


#endif /* defined(__BlindChef__ScoreUserEntity__) */
