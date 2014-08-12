
#ifndef __BlindChef__Chicken__
#define __BlindChef__Chicken__

#include "cocos2d.h"
#include "Food.h"

class Chicken : public Food {
public:
    static Chicken* create();
    
    bool init();
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Chicken__) */
