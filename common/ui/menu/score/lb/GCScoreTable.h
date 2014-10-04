
#ifndef __BlindChef__GCScoreTable__
#define __BlindChef__GCScoreTable__

#include "cocos2d.h"
#include <extensions/cocos-ext.h>
#include "network/HttpRequest.h"
#include "network/HttpClient.h"

#include "UserScoreResult.h"

class GCScoreTable :  public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
private:
    cocos2d::extension::TableView* _tableView;
    cocos2d::Size _winSize;
    UserScoreResult *_result;
    cocos2d::Vector<cocos2d::Sprite *> _sprites;
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    cocos2d::Layer* createCell(cocos2d::Ref* data, int index);
    cocos2d::Label* createLabel(std::string text, cocos2d::TTFConfig ttf, cocos2d::Color3B color);
public:
    GCScoreTable();
    ~GCScoreTable();
    
    bool init(cocos2d::Size viewSize);
    
    void onComplete(Ref *pSender);
    void onError(Ref *pSender);
    void onImageDownLoaded(cocos2d::network::HttpClient* pSender, cocos2d::network::HttpResponse* pResponse);
};

#endif /* defined(__BlindChef__GCScoreTable__) */
