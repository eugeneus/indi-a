
#ifndef __BlindChef__PerformanceMetrics__
#define __BlindChef__PerformanceMetrics__

#include "cocos2d.h"

class PerformanceMetrics {

public:

   PerformanceMetrics();

   ~PerformanceMetrics();

   static PerformanceMetrics* create();

   bool init();
    
    int getNextDishLevel();
    int getNextIngridientRepeats();
    int getNextMetricType();
    float getNextMetricValue(int anIndex);

protected:
    
    int _ingridientRepeats;
    int _dishLevel;
    std::vector<float> _metricValue;
    std::vector<bool> _metricUsage;
    
    std::vector<int> _bonusIDs; //TODO
    std::vector<int> _bonusRepeats; //TODO
    
    float _roundTime; //TODO
    

private:
    

};
#endif /* defined(__BlindChef__PerformanceMetrics__) */
