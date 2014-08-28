
#ifndef __BlindChef__Spice__
#define __BlindChef__Spice__

#include "cocos2d.h"
#include "Food.h"

class Spice : public Food {
public:
    static Spice* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Spice__) */
