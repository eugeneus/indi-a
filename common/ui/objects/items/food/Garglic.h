
#ifndef __BlindChef__Garglic__
#define __BlindChef__Garglic__

#include "cocos2d.h"
#include "Food.h"

class Garglic : public Food {
public:
    static Garglic* create();
    
    bool init();
    
private:
    typedef Food super;
    
};


#endif /* defined(__BlindChef__Garglic__) */
