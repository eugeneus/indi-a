
#include "PerformanceMetrics.h"

PerformanceMetrics::PerformanceMetrics(){}


PerformanceMetrics::~PerformanceMetrics() {}

PerformanceMetrics* PerformanceMetrics::create()
{
    PerformanceMetrics *pRet = new PerformanceMetrics();
    if (!(pRet && pRet->init()))
    {
        delete pRet;
        pRet = NULL;
    }
    
    return pRet;
}

bool PerformanceMetrics::init()
{
    _ingridientRepeats = 3;
    _dishLevel = 2;
    _metricValue.push_back(0.1f); //speed
    _metricUsage.push_back(false);
    _metricValue.push_back(0.1f); //garbage percent
    _metricUsage.push_back(false);
    _metricValue.push_back(0.1f); // items density
    _metricUsage.push_back(false);

   return true;
}

int PerformanceMetrics::getNextDishLevel()
{
    if (_dishLevel > 4){
        _dishLevel = 2;
    }
    return _dishLevel++;
}

int PerformanceMetrics::getNextIngridientRepeats()
{
    if (_ingridientRepeats > 3){
        _ingridientRepeats = 1;
    }
    return _ingridientRepeats++;

}

int PerformanceMetrics::getNextMetricType()
{
    std::vector<bool>::iterator it = _metricUsage.begin();
    std::vector<bool>::iterator end = _metricUsage.end();
    //std::vector<bool>::iterator end = _metricUsage.end();
    
    it = std::find(_metricUsage.begin(), _metricUsage.end(), false);
    
    if(it == _metricUsage.end()){
        std::fill(_metricUsage.begin(), _metricUsage.end(), false);
        it = _metricUsage.begin();
    }
    
    return std::distance(_metricUsage.begin(), it);
    
}

float PerformanceMetrics::getNextMetricValue(int anIndex)
{
    if(_metricValue[anIndex] > 1.0f){
        _metricValue[anIndex] = 0.1f;
    }
    return  _metricValue[anIndex]++;
}


