
#include "SlidingDataSource.h"

SlidingDataSource::SlidingDataSource() {}
SlidingDataSource::~SlidingDataSource() {}

ssize_t SlidingDataSource::getDataSize() {
    return _data.size();
}

std::vector<Ref *> SlidingDataSource::getData() {
    return _data;
}

void SlidingDataSource::requestData(SlidingDataSourceCallback *callback) {
    _callback = callback;
    this->requestData();
}

void SlidingDataSource::dataRequestComplete(std::vector<Ref *> data) {
    for (Ref* d : data) {
        _data.push_back(d);
    }
    
    _callback->requestDataComplete();
}