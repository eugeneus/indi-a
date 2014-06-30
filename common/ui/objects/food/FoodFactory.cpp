
#include "FoodFactory.h"
#include "Gabbage.h"

Food* FoodFactory::createFood(int food_type)
{
    Food* food;
    switch(food_type)
    {
        case kFoodGabbge:
        {
            food = Gabbage::create();
            break;
        }
        
        default:
        {
            food = NULL;
            break;
        }
    }
    return food;
}
