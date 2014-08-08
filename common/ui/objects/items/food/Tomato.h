
#ifndef __BlindChef__Tomato__
#define __BlindChef__Tomato__

#include "cocos2d.h"
#include "Food.h"

class Tomato : public Food {
public:
    static Tomato* create();
    
    bool init();
    
private:
    typedef Food super;
    
};

#endif /* defined(__BlindChef__Tomato__) */
