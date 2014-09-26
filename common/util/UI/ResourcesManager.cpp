#include "ResourcesManager.h"

ResourcesManager* ResourcesManager::_instance = nullptr;
ResourcesManager::ResourcesManager(){}
ResourcesManager::~ResourcesManager() {}

ResourcesManager* ResourcesManager::getInstance()
{
    
    
    if (! _instance)
    {
        _instance = new ResourcesManager();
        if (_instance && _instance->init())
        {
            return _instance;
        }
        else
        {
            delete _instance;
            _instance = NULL;
            return NULL;
        }
        
    }
    
    return _instance;
}

bool ResourcesManager::init()
{
    
    
    
    return true;
}

void ResourcesManager::setScreenSize(cocos2d::Size size) {
    _size = size;
    
    this->initializeData();
}

std::string ResourcesManager::getResourcesPlistFileName() {
    return _plist;
}

std::string ResourcesManager::getResourcesImagesFileName() {
    return _images;
}

float ResourcesManager::getResolutionWidth() {
    return _resolutionWidth;
}

float ResourcesManager::getResolutionHeight() {
    return _resolutionHeight;
}

ResolutionPolicy ResourcesManager::getResolutionPolicy() {
    return _resolutionPolicy;
}

float ResourcesManager::getBottomOffset() {
    return _bottomOffset;
}

void ResourcesManager::initializeData() {
    
    _bottomOffset = 0;
    
    if (2048 == _size.width || 2048 == _size.height) {
        _resolutionPolicy = ResolutionPolicy::NO_BORDER;
        _resolutionHeight = 2048;
        _resolutionWidth = 1536;
        _images = "images.png";
        _plist = "images.plist";
    } else if (1024 == _size.width || 1024 == _size.height) {
        _resolutionPolicy = ResolutionPolicy::NO_BORDER;
        _resolutionHeight = 1024;
        _resolutionWidth = 768;
        _images = "images.png";
        _plist = "images.plist";
    } else if (1136 == _size.width || 1136 == _size.height) {
        _resolutionPolicy = ResolutionPolicy::SHOW_ALL;
        _resolutionHeight = 1136;
        _resolutionWidth = 640;
        _images = "images640x1136.png";
        _plist = "images640x1136.plist";
        
        _bottomOffset = 176;
        
    } else if (960 == _size.width || 960 == _size.height) {
        _resolutionPolicy = ResolutionPolicy::NO_BORDER;
        _resolutionHeight = 960;
        _resolutionWidth = 640;
        _images = "images.png";
        _plist = "images.plist";
    } else if (480 == _size.width || 480 == _size.height) {
        _resolutionPolicy = ResolutionPolicy::SHOW_ALL;
        _resolutionHeight = 480;
        _resolutionWidth = 320;
        _images = "images320x480.png";
        _plist = "images320x480.plist";
    }
}