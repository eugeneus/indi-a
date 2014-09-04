#ifndef __BlindChef__ScoreDto__
#define __BlindChef__ScoreDto__

#include "cocos2d.h"

USING_NS_CC;

class ScoreDto : public cocos2d::Ref
{
private:
    std::string _name;
    std::string _photo;
    int _score;
public:
    
    static ScoreDto* create(std::string name, std::string photo, int score);
    virtual bool init(std::string name, std::string photo, int score);
    ScoreDto();
    virtual ~ScoreDto();
    
    std::string getName();
    std::string getPhoto();
    int getScore();
};

#endif /* defined(__BlindChef__ScoreDto__) */
