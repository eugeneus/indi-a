
#ifndef __BlindChef__Gabbage__
#define __BlindChef__Gabbage__

#include "cocos2d.h"
#include "Food.h"

class Gabbage : public Food {
public:
    static Gabbage* create();
    
    bool init();

private:
   typedef Food super;

};


#endif /* defined(__BlindChef__Gabbage__) */
