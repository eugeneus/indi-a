
#include "Overview.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

Overview::Overview() {}
Overview::~Overview() {CCLOG("-------end------");}

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
        
        _loadingBg = Sprite::createWithSpriteFrameName("bg_popup.png");
        this->addChild(_loadingBg, 1000);
        _loading = Sprite::createWithSpriteFrameName("bottle_1.png");
        this->addChild(_loading, 1001);
        _loadingAction = RepeatForever::create(RotateBy::create(5.0, 360));
        _loading->runAction(_loadingAction);
        
        
        SEL_CallFuncO func1 = callfuncO_selector(Overview::onComplete);
        NotificationCenter::getInstance()->addObserver(this, func1, "table_score_complete", nullptr);
        
        SEL_CallFuncO func2 = callfuncO_selector(Overview::onError);
        NotificationCenter::getInstance()->addObserver(this, func2, "table_score_error", nullptr);
        
        
        _dataSource->requestData(this);
        
        
        
        bRet = true;
    }while(0);
    return bRet;
}

void Overview::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log("cell touched at index %zd", cell->getIdx());
}

cocos2d::Size Overview::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return cocos2d::Size(winSize.width,winSize.height/6);
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
    this->toggleLoading();
}

void Overview::toggleLoading() {
    bool visibility = false;
    
    if (!_loading->isVisible()) {
        visibility = true;
    }
    _loading->setVisible(visibility);
    _loadingBg->setVisible(visibility);
}

void Overview::onComplete(Ref *pSender) {
    CCLOG("fdsfsd");
    this->requestDataComplete();
}

void Overview::onError(Ref *pSender) {

}