
#ifndef __BlindChef__Beef__
#define __BlindChef__Beef__

#include "cocos2d.h"
#include "Food.h"

class Beef : public Food {
public:
    static Beef* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Beef__) */
