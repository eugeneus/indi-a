
#ifndef __BlindChef__LevelProvider__
#define __BlindChef__LevelProvider__

#include "cocos2d.h"
USING_NS_CC;

class LevelProvider : public cocos2d::Ref {
private:
    int _levelId;
    cocos2d::ValueMap _levelMap;
public:
    LevelProvider();
    
    ~LevelProvider();
    
    static LevelProvider* createForLevel(int levelId);
    
    bool initForLevel(int levelId);
    
    
    float getSpeed();
    std::vector<int> getRequiredItems();
    std::vector<int> getAllowedFoodItems();
    std::vector<int> getAllowedGarbageItems();
};

#endif /* defined(__BlindChef__LevelProvider__) */
