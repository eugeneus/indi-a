
#ifndef __BlindChef__Bread__
#define __BlindChef__Bread__

#include "cocos2d.h"
#include "Food.h"

class Bread : public Food {
public:
    static Bread* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Bread__) */
