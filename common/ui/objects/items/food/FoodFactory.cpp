
#include "FoodFactory.h"
#include "Gabbage.h"
#include "Potatoe.h"
#include "Garglic.h"
#include "Tomato.h"
#include "Chicken.h"
#include "Pepps.h"
#include "Egg.h"

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
        case kFoodPotatoe:
        {
            food = Potatoe::create();
            break;
        }
        case kFoodGarglic:
        {
            food = Garglic::create();
            break;
        }
        case kFoodTomato:
        {
            food = Tomato::create();
            break;
        }
        case kFoodChicken:
        {
            food = Chicken::create();
            break;
        }
        case kFoodPepps:
        {
            food = Pepps::create();
            break;
        }
        case kFoodEgg:
        {
            food = Egg::create();
            break;
        }
            
            
        default:
        {
            food = Potatoe::create();
            break;
        }
    }
    return food;
}
