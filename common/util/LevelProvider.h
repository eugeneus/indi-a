
#ifndef __BlindChef__LevelProvider__
#define __BlindChef__LevelProvider__

#include "cocos2d.h"
USING_NS_CC;

class LevelProvider : public cocos2d::Ref {
private:
    int _levelId;
    cocos2d::ValueMap _levelMap;
    
    std::vector<int> _requiredItems;
    std::vector<int> _allowedFoodItems;
    std::vector<int> _allowedGarbageItems;
public:
    LevelProvider();
    
    ~LevelProvider();
    
    static LevelProvider* createForLevel(int levelId);
    
    bool initForLevel(int levelId);
    
    
    float getSpeed();
    std::vector<int> getRequiredItems();
    std::vector<int> getAllowedFoodItems();
    std::vector<int> getAllowedGarbageItems();
    
    bool isRequiredItem(int itemId);
};

#endif /* defined(__BlindChef__LevelProvider__) */
