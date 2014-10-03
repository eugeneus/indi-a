
#include "FBScoreTable.h"
#include "FBManager.h"
#include "ScoreUserEntity.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"


USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

FBScoreTable::FBScoreTable() {
    _result = nullptr;
}
FBScoreTable::~FBScoreTable() {CCLOG("-------end------");}

bool FBScoreTable::init(cocos2d::Size viewSize)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!cocos2d::Layer::init());
        
        _winSize = Director::getInstance()->getWinSize();
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
        
        SEL_CallFuncO func1 = callfuncO_selector(FBScoreTable::onComplete);
        NotificationCenter::getInstance()->addObserver(this, func1, "score_complete", nullptr);
        
        SEL_CallFuncO func2 = callfuncO_selector(FBScoreTable::onError);
        NotificationCenter::getInstance()->addObserver(this, func2, "score_error", nullptr);
        
        
        [FBManager getScoreList];
        
        bRet = true;
    }while(0);
    return bRet;
}

void FBScoreTable::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log("cell touched at index %zd", cell->getIdx());
}

cocos2d::Size FBScoreTable::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    return cocos2d::Size(_winSize.width, 120);
}

TableViewCell* FBScoreTable::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    log("idx = %zd",idx);

    Ref* data = _result->getData().at(idx);
    Layer* item = this->createCell(data, idx);
    cell->addChild(item);
    
    return cell;
}

ssize_t FBScoreTable::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    if ( _result == nullptr || _result == NULL || !_result) return 0;
    
    return _result->getData().size();
}

void FBScoreTable::onComplete(Ref *pSender) {
    CCLOG("complete");
    
    _sprites.clear();
    
    if (pSender != nullptr) {
        _result = (UserScoreResult *) pSender;
    }
    
    _tableView->reloadData();
}

void FBScoreTable::onError(Ref *pSender) {
    CCLOG("error");
}

Label* FBScoreTable::createLabel(std::string text, TTFConfig ttf, Color3B color) {
    Label* label = Label::createWithTTF(ttf, text);
    label->setAnchorPoint(Vec2(0,0));
    label->setColor(color);
    
    return label;
}

Layer* FBScoreTable::createCell(Ref* data, int index) {
    if (!data) return Layer::create();
    
    ScoreUserEntity* dto = (ScoreUserEntity *) data;
    
    TTFConfig ttf32;
    ttf32.fontSize = 32;
    ttf32.fontFilePath = "crystal radio kit.ttf";
    
    TTFConfig ttf18;
    ttf18.fontSize = 18;
    ttf18.fontFilePath = "crystal radio kit.ttf";
    
    const cocos2d::Color3B& colorWhite = Color3B(255, 255, 255);
    
    Label* label = createLabel(dto->getName(), ttf32, colorWhite);
    label->setPosition(Vec2(label->getPosition().x + 120, label->getPosition().y));
    //label->setPosition(Vec2());
    
    Label* labelScore = createLabel(CCString::createWithFormat("%i", dto->getScore())->getCString(), ttf18, colorWhite);
    labelScore->setPosition(Vec2(labelScore->getPosition().x + 120, labelScore->getPosition().y  - 30));
    const char *url = CCString::createWithFormat("https://graph.facebook.com/%s/picture?type=square", dto->getImageUrl().c_str())->getCString();
    CCLOG("----- %s", url);
    cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
    request->setUrl(url);
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(FBScoreTable::onImageDownLoaded, this));
    request->setTag(CCString::createWithFormat("%i", index)->getCString());//dto->getImageUrl().c_str());
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    
    Sprite *logo = Sprite::create("no_img.png"); //SpriteFrameName("again_btn.png");
    logo->setPosition(Vec2(logo->getPosition().x + 50, logo->getPosition().y));
    logo->setTag(index);
    _sprites.pushBack(logo);
    
    Layer *result = Layer::create();
    result->addChild(label);
    result->addChild(labelScore);
    result->addChild(logo);
    
    return result;
}

void FBScoreTable::onImageDownLoaded(cocos2d::network::HttpClient* pSender, cocos2d::network::HttpResponse* pResponse)
{
    cocos2d::network::HttpResponse* response = pResponse;
    
    if (!response)
    {
        CCLOG("No Response");
        return;
    }
    
    int statusCode = response->getResponseCode();
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLOG("response code: %d", statusCode);
    
    int intTag = std::stoi(response->getHttpRequest()->getTag());//(int) response->getHttpRequest()->getTag();
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    std::vector<char>*buffer = response->getResponseData();
    
    Image * img=new Image();
    img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
    
    // Save image file to device.
   /* std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath.append(response->getHttpRequest()->getTag());
    img->saveToFile(writablePath.c_str());
    */
    Texture2D* texture = new Texture2D();
    texture->initWithImage(img);
    
    
    for (Sprite *sprite : _sprites) {
        if (sprite->getTag() == intTag) {
            sprite->setTexture(texture);//setTexture(texture);
        }
    }
}