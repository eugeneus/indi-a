
#ifndef __BlindChef__Overview__
#define __BlindChef__Overview__

#include <iostream>
#include "cocos2d.h"
#include <extensions/cocos-ext.h>

#include "SlidingDataSource.h"
#include "SlidingItemRenderer.h"
#include "SlidingDataSourceCallback.h"

USING_NS_CC;

class Overview : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate, public SlidingDataSourceCallback
{
private:
    SlidingDataSource* _dataSource;
    SlidingItemRenderer* _renderer;
    cocos2d::extension::TableView* _tableView;
    cocos2d::Sprite* _loading;
    cocos2d::Sprite* _loadingBg;
    cocos2d::Action* _loadingAction;
    
protected:
    void toggleLoading();
public:
    Overview();
    ~Overview();
    virtual bool init(SlidingDataSource* dataSource, SlidingItemRenderer* renderer, cocos2d::Size viewSize);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};//滑动
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};  //放大
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);//触摸事件
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);//Cell大小
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);//添加Cell
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);//设置Cell个数
    
    
    
    void requestDataComplete();
//    void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);//触摸事件
    
//    void addMenuTouchEvent(const menuCallBack& callback);//回调函数
    
    Size winSize;
    cocos2d::Ref* _pSender;
};

#endif /* defined(__BlindChef__Overview__) */
