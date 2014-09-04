
#include "ScoreDto.h"

USING_NS_CC;

ScoreDto::ScoreDto() {}
ScoreDto::~ScoreDto() {}

ScoreDto* ScoreDto::create(std::string name, std::string photo, int score) {
    ScoreDto *pRet = new ScoreDto();
    if (pRet && pRet->init(name, photo, score))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }

}

bool ScoreDto::init(std::string name, std::string photo, int score) {
    _name = name;
    _photo = photo;
    _score = score;
    
    return true;
}

std::string ScoreDto::getName() {
    return _name;
}

std::string ScoreDto::getPhoto() {
    return _photo;
}

int ScoreDto::getScore() {
    return _score;
}