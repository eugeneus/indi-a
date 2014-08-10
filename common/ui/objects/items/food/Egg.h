
#ifndef __BlindChef__Egg__
#define __BlindChef__Egg__

#include "cocos2d.h"
#include "Food.h"

class Egg : public Food {
public:
    static Egg* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Egg__) */
