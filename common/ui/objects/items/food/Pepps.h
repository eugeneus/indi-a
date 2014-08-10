
#ifndef __BlindChef__Pepps__
#define __BlindChef__Pepps__

#include "cocos2d.h"
#include "Food.h"

class Pepps : public Food {
public:
    static Pepps* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Pepps__) */
