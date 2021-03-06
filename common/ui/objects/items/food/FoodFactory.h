
#ifndef __BlindChef__FoodFactory__
#define __BlindChef__FoodFactory__

#include "Food.h"

enum
{
    kFoodGabbge = 0,
    kFoodPotatoe,  // 1
    kFoodGarglic,  // 2
    kFoodTomato,   // 3
    kFoodChicken,  // 4
    kFoodPepps,    // 5
    kFoodEgg,      // 6
    kFoodOnion,    // 7
    kFoodCarrots,  // 8
    kFoodMushrroom,// 9
    kFoodBread,    //10
    kFoodCheese,   //11
    kFoodBeef,     //12
    kFoodLemon,    //13
    kFoodSalt,     //14
    kFoodSpice,     //15
    kNoodles,        //16 TODO: add this food
    kCelery         //17 TODO: add this food
};

class FoodFactory {
    
public:
    static Food* createFood(int food_type);
};

#endif /* defined(__BlindChef__FoodFactory__) */
