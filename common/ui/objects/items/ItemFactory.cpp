
#include "ItemFactory.h"
#include "FoodFactory.h"
#include "GarbageFactory.h"

Item* ItemFactory::createItem(int item_type, int sub_item_type)
{
    Item* item;
    switch(item_type)
    {
        case kItemFood:
        {
            item = FoodFactory::createFood(sub_item_type);
            break;
        }
        case kItemGarbage: {
            
            item = GarbageFactory::createGarbage(sub_item_type);
            break;
        }
            
        default:
        {
            item = NULL;
            break;
        }
    }
    return item;
}
