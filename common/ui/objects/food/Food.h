
#ifndef __BlindChef__Food__
#define __BlindChef__Food__

#include "cocos2d.h"
#include "Spritable.h"

class Food : public Spritable {
private:
    typedef Spritable super;
public:
    
    bool initWithSpriteAndPos(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime);
    //   virtual void initializeMenu();
    
};

#endif /* defined(__BlindChef__Food__) */
