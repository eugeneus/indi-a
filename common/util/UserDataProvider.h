
#ifndef __BlindChef__UserDataProvider__
#define __BlindChef__UserDataProvider__

#include "cocos2d.h"
USING_NS_CC;

class UserDataProvider : public cocos2d::Ref {
private:
    //cocos2d::ValueMap _dataMap;
    static UserDataProvider* _instance;
    UserDataProvider();
    
    ~UserDataProvider();
protected:
    bool getBoolValue(const char* key);
    void updateBoolValue(const char* key, bool value);
    
    int getIntegerValue(const char* key);
    void updateIntegerValue(const char* key, int value);
public:
    
    
    static UserDataProvider* getInstance();
    
    bool init();
    
    bool isFirstLaunch();
    void updateFirstLaunch(bool value);
    
    int getUserScore();
    void updateUserScore(int pScore);
    
    int getBestUserScore();
    void updateBestUserScore(int pScore);
    
    int getUserLives();
    void updateUserLives(int pLives);
    
    int getDishesCount();
    void updateDishesCount(int pCount);
    
    int getBonus1Count();
    void updateBonus1Count(int pCount);
    
    int getBonus2Count();
    void updateBonus2Count(int pCount);
    
    int getBonus3Count();
    void updateBonus3Count(int pCount);
    
    bool isSoundOn();
    void setSoundOn(bool isSoundOn);
    
    bool isMusicOn();
    void setMusicOn(bool isMusicOn);
    
    bool isNotificationOn();
    void setNotificationOn(bool isNotificationOn);
    
    std::string getLiveTimeout(int index);
    void updateLiveTimeout(int index, std::string count);
};

#endif /* defined(__BlindChef__UserDataProvider__) */
