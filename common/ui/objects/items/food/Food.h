
#ifndef __BlindChef__Food__
#define __BlindChef__Food__

#include "cocos2d.h"
#include "Item.h"

class Food : public Item {
private:
    typedef Item super;
public:
    
    bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    //   virtual void initializeMenu();
    
};

#endif /* defined(__BlindChef__Food__) */
