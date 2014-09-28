
#include "ScoreUserEntity.h"
USING_NS_CC;

ScoreUserEntity* ScoreUserEntity::create(std::string pName, std::string pImageUrl, int pScore) {
    ScoreUserEntity *pRet = new ScoreUserEntity();
    if (pRet && pRet->init(pName, pImageUrl, pScore))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ScoreUserEntity::init(std::string pName, std::string pImageUrl, int score) {
    //if (!init()) return false;
    
    _name = pName;
    _imageUrl = pImageUrl;
    _score = score;
    
    return true;
}

std::string ScoreUserEntity::getName() {
    return _name;
}

std::string ScoreUserEntity::getImageUrl() {
    return _imageUrl;
}

int ScoreUserEntity::getScore() {
    return _score;
}