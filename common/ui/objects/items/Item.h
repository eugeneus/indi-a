
#ifndef __BlindChef__Item__
#define __BlindChef__Item__

#include "cocos2d.h"
#include "Spritable.h"

class Item : public Spritable {
private:
    typedef Spritable super;
public:
    
    bool init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    //   virtual void initializeMenu();
    
};

#endif /* defined(__BlindChef__Item__) */
