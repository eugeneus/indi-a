
#ifndef __BlindChef__ResourcesManager__
#define __BlindChef__ResourcesManager__

#include "cocos2d.h"
USING_NS_CC;

class ResourcesManager : public cocos2d::Ref {
private:
    float _resolutionWidth;
    float _resolutionHeight;
    ResolutionPolicy _resolutionPolicy;
    std::string _plist;
    std::string _images;
    cocos2d::Size _size;
    //cocos2d::ValueMap _dataMap;
    static ResourcesManager* _instance;
    ResourcesManager();
    
    ~ResourcesManager();
protected:
    void initializeData();
public:
    
    
    static ResourcesManager* getInstance();
    
    bool init();
    
    void setScreenSize(cocos2d::Size size);
    std::string getResourcesPlistFileName();
    std::string getResourcesImagesFileName();
    
    float getResolutionWidth();
    float getResolutionHeight();
    ResolutionPolicy getResolutionPolicy();
    
};

#endif /* defined(__BlindChef__ResourcesManager__) */
