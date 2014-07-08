
#ifndef __BlindChef__Garbage__
#define __BlindChef__Garbage__

#include "cocos2d.h"
#include "Item.h"

class Garbage : public Item {
private:
    typedef Item super;
public:
    
    bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    //   virtual void initializeMenu();
    
};

#endif /* defined(__BlindChef__Garbage__) */
