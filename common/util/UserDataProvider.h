
#ifndef __BlindChef__UserDataProvider__
#define __BlindChef__UserDataProvider__

#include "cocos2d.h"
USING_NS_CC;

class UserDataProvider : public cocos2d::Ref {
private:
    //cocos2d::ValueMap _dataMap;
public:
    UserDataProvider();
    
    ~UserDataProvider();
    
    static UserDataProvider* create();
    
    bool init();
    
    int getUserScore();
    void updateUserScore(int pScore);
    
    
};

#endif /* defined(__BlindChef__UserDataProvider__) */
