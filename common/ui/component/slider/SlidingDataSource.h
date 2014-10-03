
#ifndef __BlindChef__SlidingDataSource__
#define __BlindChef__SlidingDataSource__

#include "cocos2d.h"
#include "SlidingDataSourceCallback.h"

USING_NS_CC;

class SlidingDataSource : public cocos2d::Ref
{
private:
    SlidingDataSourceCallback *_callback;
protected:
    cocos2d::Vector<Ref *> _data;
public:
    SlidingDataSource();
    virtual ~SlidingDataSource();
    
    ssize_t getDataSize();
    cocos2d::Vector<Ref *> getData();
    
    void requestData(SlidingDataSourceCallback *callback);
    void dataRequestComplete(cocos2d::Vector<Ref *> data);
    
    virtual void requestData() = 0;
    SlidingDataSourceCallback *getCallback();
    //virtual void requestComplete();
};

#endif /* defined(__BlindChef__SlidingDataSource__) */
