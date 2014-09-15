
#ifndef __BlindChef__DishFactory__
#define __BlindChef__DishFactory__

#include "cocos2d.h"
class Dish;

class DishFactory {

public:

   DishFactory();

   ~DishFactory();

   static DishFactory* create(const char* aFileName);

   bool init(const char* aFileName);
    
    Dish* getRandomDish();
    
protected:
    
    cocos2d::ValueMap _dishesMap;
    
    
private:


};
#endif /* defined(__BlindChef__DishFactory__) */
