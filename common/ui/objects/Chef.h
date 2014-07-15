
#ifndef __BlindChef__Chef__
#define __BlindChef__Chef__

#include "cocos2d.h"
#include "Spritable.h"

class Chef : public Spritable {
private:
    typedef Spritable super;
public:
    static Chef* create();
    //static cocos2d::Scene* createScene();
    
    bool init();
 //   virtual void initializeMenu();

};

#endif /* defined(__BlindChef__Chef__) */
