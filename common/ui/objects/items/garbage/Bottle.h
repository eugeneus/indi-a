
#ifndef __BlindChef__Bottle__
#define __BlindChef__Bottle__

#include "cocos2d.h"
#include "Garbage.h"

class Bottle : public Garbage {
private:
    typedef Garbage super;
public:
    static Bottle* create();
    
    bool init();
};


#endif /* defined(__BlindChef__Bottle__) */
