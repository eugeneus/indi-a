
#ifndef __BlindChef__Lemon__
#define __BlindChef__Lemon__


#include "cocos2d.h"
#include "Food.h"

class Lemon : public Food {
public:
    static Lemon* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Lemon__) */
