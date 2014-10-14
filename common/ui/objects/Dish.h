
#ifndef __BlindChef__Dish__
#define __BlindChef__Dish__

#include "cocos2d.h"


class Dish {
public:

   Dish();

   ~Dish();

   static Dish* create(const std::string& anImageFileName, const std::vector<int>& anIngridientIDsList);

   bool init(const std::string& anImageFileName, const std::vector<int>& anIngridientIDsList);
    
    std::string getImageName();
    std::vector<int> getIngridientIDs();
    bool checkAllRequiredExist(std::vector<int> itemsIds);
    bool isRequiredItem(int anItemId);

protected:
    
    std::vector<int> _ingridientIDs;
    std::string _imageFileName;
    std::string _name;
    int _ingridients;

private:

};
#endif /* defined(__BlindChef__Dish__) */
