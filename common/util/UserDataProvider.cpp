
#include "UserDataProvider.h"

UserDataProvider* UserDataProvider::_instance = nullptr;
UserDataProvider::UserDataProvider(){}
UserDataProvider::~UserDataProvider() {}

UserDataProvider* UserDataProvider::getInstance()
{
    
    
    if (! _instance)
    {
        _instance = new UserDataProvider();
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

bool UserDataProvider::init()
{
    
    //UserDefaut::getInstance()->getIntegerForKey("");
    
    return true;
}

bool UserDataProvider::isFirstLaunch() {
    return this->getBoolValue("first_launch");
}

void UserDataProvider::updateFirstLaunch(bool value) {
    this->updateBoolValue("first_launch", value);
}

int UserDataProvider::getUserScore() {
    return this->getIntegerValue("score");
}

void UserDataProvider::updateUserScore(int pScore) {
    this->updateIntegerValue("score", pScore);
}

int UserDataProvider::getBestUserScore() {
    return this->getIntegerValue("best_score");
}

void UserDataProvider::updateBestUserScore(int pScore) {
    this->updateIntegerValue("best_score", pScore);
}

bool UserDataProvider::getBoolValue(const char* key) {
    return UserDefault::getInstance()->getBoolForKey(key);
}

std::string UserDataProvider::getLiveTimeout(int index) {
    return UserDefault::getInstance()->getStringForKey(CCString::createWithFormat("lives%i", index)->getCString());
}

void UserDataProvider::updateLiveTimeout(int index, std::string count) {
    UserDefault::getInstance()->setStringForKey(CCString::createWithFormat("lives%i", index)->getCString(), count);
    UserDefault::getInstance()->flush();
}

void UserDataProvider::updateBoolValue(const char* key, bool value) {
    UserDefault::getInstance()->setBoolForKey(key, value);
    UserDefault::getInstance()->flush();
}

int UserDataProvider::getIntegerValue(const char* key) {
    return UserDefault::getInstance()->getIntegerForKey(key);
}

void UserDataProvider::updateIntegerValue(const char* key, int value) {
    UserDefault::getInstance()->setIntegerForKey(key, value);
    UserDefault::getInstance()->flush();
}

int UserDataProvider::getUserLives() {
    return this->getIntegerValue("user_lives");
}

void UserDataProvider::updateUserLives(int pLives) {
    this->updateIntegerValue("user_lives", pLives);
}

bool UserDataProvider::isSoundOn() {
    return this->getBoolValue("sound_on");
}

void UserDataProvider::setSoundOn(bool isSoundOn) {
    this->updateBoolValue("sound_on", isSoundOn);
}

bool UserDataProvider::isMusicOn() {
    return this->getBoolValue("music_on");
}

void UserDataProvider::setMusicOn(bool isMusicOn) {
    this->updateBoolValue("music_on", isMusicOn);
}

bool UserDataProvider::isNotificationOn() {
    return this->getBoolValue("notification_on");
}

void UserDataProvider::setNotificationOn(bool isNotificationOn) {
    this->updateBoolValue("notification_on", isNotificationOn);
}

int UserDataProvider::getBonus1Count() {
    return this->getIntegerValue("bonus1_count");
}

void UserDataProvider::updateBonus1Count(int pCount) {
    this->updateIntegerValue("bonus1_count", pCount);
}

int UserDataProvider::getBonus2Count() {
    return this->getIntegerValue("bonus2_count");
}

void UserDataProvider::updateBonus2Count(int pCount) {
    this->updateIntegerValue("bonus2_count", pCount);
}

int UserDataProvider::getBonus3Count() {
    return this->getIntegerValue("bonus3_count");
}

void UserDataProvider::updateBonus3Count(int pCount) {
    this->updateIntegerValue("bonus3_count", pCount);
}

int UserDataProvider::getDishesCount() {
    return this->getIntegerValue("dishes_count");
}

void UserDataProvider::updateDishesCount(int pCount) {
    this->updateIntegerValue("dishes_count", pCount);
}