
#include "SlidingDataSource.h"

SlidingDataSource::SlidingDataSource() {}
SlidingDataSource::~SlidingDataSource() {}

ssize_t SlidingDataSource::getDataSize() {
    return _data.size();
}

cocos2d::Vector<Ref *> SlidingDataSource::getData() {
    return _data;
}

void SlidingDataSource::requestData(SlidingDataSourceCallback *callback) {
    _callback = callback;
    this->requestData();
}

void SlidingDataSource::dataRequestComplete(cocos2d::Vector<Ref *> data) {
    for (Ref* d : data) {
        _data.pushBack(d);
    }
    
    _callback->requestDataComplete();
}

SlidingDataSourceCallback *SlidingDataSource::getCallback() {
    return _callback;
}