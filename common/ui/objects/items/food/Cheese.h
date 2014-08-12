
#ifndef __BlindChef__Cheese__
#define __BlindChef__Cheese__

#include "cocos2d.h"
#include "Food.h"

class Cheese : public Food {
public:
    static Cheese* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Cheese__) */
