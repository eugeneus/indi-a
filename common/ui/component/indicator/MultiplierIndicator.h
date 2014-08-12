
#ifndef __BlindChef__MultiplierIndicator__
#define __BlindChef__MultiplierIndicator__

#include "cocos2d.h"
#include "BaseIndicator.h"

class MultiplierIndicator : public BaseIndicator {
private:
    typedef BaseIndicator super;
    
public:
    MultiplierIndicator();
    virtual ~MultiplierIndicator();
    static MultiplierIndicator* create();
    
    bool init();
    
    void nextStep(int step);
    void reset();
};

#endif /* defined(__BlindChef__MultiplierIndicator__) */
