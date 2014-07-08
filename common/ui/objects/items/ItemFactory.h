

#ifndef __BlindChef__ItemFactory__
#define __BlindChef__ItemFactory__

#include "Item.h"

enum
{
    kItemFood = 0,
    kItemGarbage
};

class ItemFactory {
    
public:
    static Item* createItem(int item_type, int sub_item_type);
};

#endif /* defined(__BlindChef__ItemFactory__) */
