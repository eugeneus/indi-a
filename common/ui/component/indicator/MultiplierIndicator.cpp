

#include "MultiplierIndicator.h"


USING_NS_CC;

MultiplierIndicator::MultiplierIndicator(){}
MultiplierIndicator::~MultiplierIndicator() {}


MultiplierIndicator* MultiplierIndicator::create()
{
    
    MultiplierIndicator *pRet = new MultiplierIndicator();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool MultiplierIndicator::init() {
    
    
    if (!super::init("multi_ind_bg.png", "multi_ind.png", false, 0.0)) {
        return false;
    }
    
    return true;
}

void MultiplierIndicator::nextStep(int step) {
    float speed = step / 4.0;
    this->doStep(speed);
}