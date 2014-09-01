
#ifndef __BlindChef__ItemsPool__
#define __BlindChef__ItemsPool__

#include "cocos2d.h"

class Item;

class ItemList:cocos2d::Ref
{
    
};


class ItemsPool {

public:

   ItemsPool();

   ~ItemsPool();

   static ItemsPool* create();

   bool init();

protected:

    cocos2d::Vector<Item*> _items; // contains overall list of items
    cocos2d::Map<int, ItemList*> _requiredPool;
private:


};
#endif /* defined(__BlindChef__ItemsPool__) */
