
#ifndef __BlindChef__Salt__
#define __BlindChef__Salt__

#include "cocos2d.h"
#include "Food.h"

class Salt : public Food {
public:
    static Salt* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Salt__) */
