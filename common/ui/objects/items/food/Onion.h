
#ifndef __BlindChef__Onion__
#define __BlindChef__Onion__

#include "cocos2d.h"
#include "Food.h"

class Onion : public Food {
public:
    static Onion* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Onion__) */
