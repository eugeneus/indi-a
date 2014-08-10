
#ifndef __BlindChef__FoodFactory__
#define __BlindChef__FoodFactory__

#include "Food.h"

enum
{
    kFoodGabbge = 0,
    kFoodPotatoe,
    kFoodGarglic,
    kFoodTomato,
    kFoodChicken,
    kFoodPepps,
    kFoodEgg
};

class FoodFactory {
    
public:
    static Food* createFood(int food_type);
};

#endif /* defined(__BlindChef__FoodFactory__) */
