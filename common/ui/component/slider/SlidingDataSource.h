
#ifndef __BlindChef__SlidingDataSource__
#define __BlindChef__SlidingDataSource__

#include "cocos2d.h"
#include "SlidingDataSourceCallback.h"

USING_NS_CC;

class SlidingDataSource : public cocos2d::Ref
{
private:
    std::vector<Ref *> _data;
    SlidingDataSourceCallback *_callback;
public:
    SlidingDataSource();
    virtual ~SlidingDataSource();
    
    ssize_t getDataSize();
    std::vector<Ref *> getData();
    
    void requestData(SlidingDataSourceCallback *callback);
    void dataRequestComplete(std::vector<Ref *> data);
    
    virtual void requestData() = 0;
    //virtual void requestComplete();
};

#endif /* defined(__BlindChef__SlidingDataSource__) */
