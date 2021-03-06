
#ifndef __BlindChef__LevelProvider__
#define __BlindChef__LevelProvider__

#include "cocos2d.h"
USING_NS_CC;

class LevelProvider : public cocos2d::Ref {
private:
    
    int _levelId;
    cocos2d::ValueMap _levelMap;
    
    float _speed;
    float _roundTime;
    std::string _bg;
    std::string _tipsBg;
    int _requiredLaunchCount; // number of times each required item should appear per round
    
    std::vector<int> _requiredItems;
    std::vector<int> _allowedFoodItems;
    std::vector<int> _allowedGarbageItems;
    std::map<int,int> _bonusItems;
    
    
public:
    
    LevelProvider();
    
    ~LevelProvider();
    
    static LevelProvider* createForLevel(int levelId);
    
    bool initForLevel(int levelId);
    
    bool checkAllRequiredExist(std::vector<int> itemsIds);
    
    int getLevelId();
    float getSpeed();
    float getRoundTime();
    std::vector<int> getRequiredItems();
    int getRequiredAppearsPerLevel();
    
    std::vector<int> getAllowedFoodItems();
    std::vector<int> getAllowedGarbageItems();
    std::map<int,int> getBonusItems();
    
    bool isRequiredItem(int itemId);
    std::string getBgSpriteFrameName();
    std::string getTipsBgSpriteFrameName();
};

#endif /* defined(__BlindChef__LevelProvider__) */
