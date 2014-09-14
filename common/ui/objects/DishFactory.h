
#ifndef __BlindChef__DishFactory__
#define __BlindChef__DishFactory__

#include "cocos2d.h"
class Dish;

class DishFactory {

public:

   DishFactory();

   ~DishFactory();

   static DishFactory* create();

   bool init();
    
    Dish* getRandomDish();
    
protected:
    
    std::vector<Dish*> _dishes;
    
private:


};
#endif /* defined(__BlindChef__DishFactory__) */
