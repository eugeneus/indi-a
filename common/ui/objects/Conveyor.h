
#ifndef __BlindChef__Conveyor__
#define __BlindChef__Conveyor__

#include "cocos2d.h"
#include "Cyclable.h"

class Conveyor : public Cyclable {
private:
    typedef Cyclable super;
public:
    static Conveyor* create(float aSpeed, float aLength);
    
    bool init(float aSpeed, float aLength);
    
    float getFirstItemPosY();
    void pauseConv();
    void resumeConv();
};

#endif /* defined(__BlindChef__Conveyor__) */
