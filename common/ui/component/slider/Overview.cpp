
#include "Overview.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

Overview::Overview() {}
Overview::~Overview() {}

bool Overview::init(SlidingDataSource *dataSource, SlidingItemRenderer* renderer, cocos2d::Size viewSize)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!cocos2d::Layer::init());
        
        _dataSource = dataSource;
        _renderer = renderer;
        
        winSize = Director::getInstance()->getWinSize();
        _tableView = TableView::create(this, viewSize);
        _tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
        _tableView->ignoreAnchorPointForPosition(false);
        _tableView->setAnchorPoint(Vec2::ZERO);
        _tableView->setPosition(Vec2::ZERO);
        _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        
        _tableView->setDelegate(this);
        this->addChild(_tableView);
        _tableView->reloadData();
        this->setTouchEnabled(true);
        
        _dataSource->requestData(this);
        
        bRet = true;
    }while(0);
    return bRet;
}

void Overview::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log("cell touched at index %zd", cell->getIdx());
}

Size Overview::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return Size(winSize.width,winSize.height/6);
}

TableViewCell* Overview::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    log("idx = %zd",idx);
    
    Ref* data = _dataSource->getData().at(idx);
    Layer* item = _renderer->create(data);
    cell->addChild(item);
    
    return cell;
}

ssize_t Overview::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _dataSource->getDataSize();
}


void Overview::requestDataComplete() {
    _tableView->reloadData();
}