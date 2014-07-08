
#ifndef __BlindChef__Conveyor__
#define __BlindChef__Conveyor__

#include "cocos2d.h"
#include "Cyclable.h"

class Conveyor : public Cyclable {
private:
    typedef Cyclable super;
public:
    static Conveyor* create();
    static cocos2d::Scene* createScene();
    
    bool init();
    
    float getFirstItemPosY();
};

#endif /* defined(__BlindChef__Conveyor__) */
