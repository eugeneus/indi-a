
#include "FoodFactory.h"
#include "Gabbage.h"
#include "Potatoe.h"
#include "Garglic.h"
#include "Tomato.h"
#include "Chicken.h"
#include "Pepps.h"
#include "Egg.h"
#include "Onion.h"
#include "Carrots.h"
#include "Mushrroom.h"
#include "Bread.h"
#include "Cheese.h"
#include "Beef.h"

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
        case kFoodOnion:
        {
            food = Onion::create();
            break;
        }
        case kFoodCarrots:
        {
            food = Carrots::create();
            break;
        }
        case kFoodMushrroom:
        {
            food = Mushrroom::create();
            break;
        }
        case kFoodBread:
        {
            food = Bread::create();
            break;
        }
        case kFoodCheese:
        {
            food = Cheese::create();
            break;
        }
        case kFoodBeef:
        {
            food = Beef::create();
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
