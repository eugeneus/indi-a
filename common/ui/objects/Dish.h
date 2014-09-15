
#ifndef __BlindChef__Dish__
#define __BlindChef__Dish__

#include "cocos2d.h"


class Dish {
public:

   Dish();

   ~Dish();

   static Dish* create(std::string anImageFileName, std::vector<int> anIngridientIDsList);

   bool init(std::string anImageFileName, std::vector<int> anIngridientIDsList);
    
    std::string getImageName();
    std::vector<int> getIngridientIDs();

protected:
    
    std::vector<int> _ingridientIDs;
    std::string _imageFileName;

private:

};
#endif /* defined(__BlindChef__Dish__) */
