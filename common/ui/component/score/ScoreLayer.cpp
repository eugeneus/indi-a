
#include "ScoreLayer.h"



USING_NS_CC;

ScoreLayer::ScoreLayer(){}
ScoreLayer::~ScoreLayer() {}


ScoreLayer* ScoreLayer::create(int score)
{
    
    ScoreLayer *pRet = new ScoreLayer();
    
    if (pRet && pRet->init(score))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool ScoreLayer::init(int pScore) {
    
    if (!Layer::init()) {
        return false;
    }
    
    score = pScore;
    
    TTFConfig ttfConfig;
    ttfConfig.fontSize = 32;
    ttfConfig.fontFilePath = "RioGrande.ttf";
    scoreLabel = Label::createWithTTF(ttfConfig, CCString::createWithFormat("%i", score)->getCString());
    scoreLabel->setColor(Color3B(100, 200, 200));
    this->addChild(scoreLabel);
    
    return true;
}

void ScoreLayer::updateScore(int dt) {
    //if (dt < 10) {
        score += dt;
        scoreLabel->setString(CCString::createWithFormat("%i", score)->getCString());
    /*} else if (dt < 100) {
    
    } else if (dt < 1000) {
    
    } else if (dt < 10000) {
        
    }*/
}

void ScoreLayer::update(float dt) {
	/*int direction = 1; // the score can roll in either direction
	if (score < scoreLabel->get) {
		direction = -1;
	}
	double pointChange = self.pointsPerSecond * direction * dt;
	curScore_ += pointChange;
	
	// don't let it overrun the target
	if (direction == -1 && curScore_ < self.score) {
		curScore_ = self.score;
	} else if (direction == 1 && curScore_ > self.score) {
		curScore_ = self.score;
	}
	
	// update the string
	// this is as costly as creating a new label
	// we should be using cclabelatlas
	[self setString:[NSString stringWithFormat:self.formatString, (int)curScore_]];
	
	// if we are at the score then stop updating
	if (self.score == curScore_) {
		[self unschedule:@selector(update_:)];
		updating_ = FALSE;
	}*/
}