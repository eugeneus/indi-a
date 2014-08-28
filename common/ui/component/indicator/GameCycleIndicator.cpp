
#include "GameCycleIndicator.h"

USING_NS_CC;

GameCycleIndicator::GameCycleIndicator(){}
GameCycleIndicator::~GameCycleIndicator() {}


GameCycleIndicator* GameCycleIndicator::createWithGameTime(float gameTime)
{
    
    GameCycleIndicator *pRet = new GameCycleIndicator();
    
    if (pRet && pRet->initWithGameTime(gameTime))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool GameCycleIndicator::initWithGameTime(float gameTime) {
    
    _gameTime = gameTime;
    
    if (!super::init("level_ind_bg.png", "level_ind.png", false, 0.0)) {
        return false;
    }

    return true;
}

void GameCycleIndicator::nextStep(float dt) {
    _currentTime += dt;
    float speed = _currentTime / _gameTime;
    this->doStep(speed);
}

void GameCycleIndicator::restart() {
    _currentTime = 0;
    super::restart();
}

void GameCycleIndicator::setGameTime(float gt) {
    _gameTime = gt;
}

//