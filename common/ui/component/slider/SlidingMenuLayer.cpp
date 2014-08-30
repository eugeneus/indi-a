#include "SlidingMenuLayer.h"
#include <cmath>

USING_NS_CC;

SlidingMenuLayer* SlidingMenuLayer::create(Size pContentSize, bool pIsVertical)
{
    SlidingMenuLayer *pRet = new SlidingMenuLayer();
    if (pRet && pRet->init(pContentSize, pIsVertical))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool SlidingMenuLayer::init(Size pContentSize, bool pIsVertical)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    isVertical = pIsVertical;
    rowsCount = 1;
    
    pScreenSize = Director::getInstance()->getWinSize();
    generalscalefactor = pScreenSize.height / 500 ;
    
    scrollView = cocos2d::extension::ScrollView::create(Size::ZERO);
    scrollView->setBounceable(true);
    scrollView->setClippingToBounds(true);
    scrollView->setDirection(isVertical ?  cocos2d::extension::ScrollView::Direction::VERTICAL : cocos2d::extension::ScrollView::Direction::HORIZONTAL);
    this->addChild(scrollView, 218, SCROLLVIEW_TAG);
    
    scrollContentSize = pContentSize;
    
    
  //  if (isVertical)  scrollView->setPosition(Vec2(scrollContentSize.width/2 , itemLength - scrollContentSize.height/2 * 1.0/(10 + 1)));
    
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(SlidingMenuLayer::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void SlidingMenuLayer::addItems(std::vector<SlidingMenuItem*> items) {
    
    scrollView->removeAllChildren();
    
    int i = 0;
    float contenSize = 0;
    for (SlidingMenuItem *item : items){
        
        float itemLength = isVertical ? item->getContentSize().height : item->getContentSize().width;
        contenSize +=itemLength + 30;
    
        float itemPositionSide = isVertical ? scrollContentSize.height - contenSize : contenSize;
        
        Vec2 position = isVertical ? Vec2(scrollContentSize.width/2 - (item->getContentSize().width )/2.0f, itemPositionSide) : Vec2(itemPositionSide, scrollContentSize.height/2 - (item->getContentSize().height)/2.0f);
        
        item->setPosition(position);
        scrollView->addChild(item, 1, i);
        
        
        i++;
    }
    
    scrollView->setViewSize(Size(scrollContentSize.width, scrollContentSize.height ));
    Size allScrollContentSize = isVertical ? Size(pScreenSize.width, contenSize) : Size(contenSize, pScreenSize.height);
    scrollView->setContentSize(allScrollContentSize);
}

void SlidingMenuLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) {
    Rect spritePos;
    
    if (touches.size() > 0) {
    
        Touch* touch = touches.at(0);
    
        endlocation = Director::getInstance()->convertToGL(touch->getLocation());
    
        if (abs(startlocation.x - endlocation.x) > 5){
            cocos2d::extension::ScrollView* tilesNode = (cocos2d::extension::ScrollView*) this->getChildByTag(SCROLLVIEW_TAG);
            
            Node *container = (Node *)(tilesNode->getChildren().at(0)) ;
            
            for (int i = 0 ; i < container->getChildren().size() ; i++){
                SlidingMenuItem *backsprite = (SlidingMenuItem *)container->getChildByTag(i);
                spritePos = Rect(
                                    (backsprite->getPosition().x + container->getPosition().x) ,
                                    backsprite->getPosition().y ,
                                    backsprite->getContentSize().width ,
                                    backsprite->getContentSize().height );
                
                if(spritePos.containsPoint(endlocation)){
                    CCLOG("clicked %i", i);
                    backsprite->itemClick();
                    
                    return;
                }
            }
        }
    }

}