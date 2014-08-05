
#include "TouchController.h"
#include "Item.h"
#include "GameMenu.h"
#include "GameController.h"

#define kTouchAngleTop 1
#define kTouchAngleRight 2
#define kTouchAngleBottom 3
#define kTouchAngleLeft 4

TouchController::TouchController()
{
    _startTime = 0.0f;
    _startPos = Vec2(0,0);
    
    _moveSpeed = 0.0f;
}

TouchController::~TouchController() {}

TouchController* TouchController::createWithLayer(cocos2d::Layer* aGameLayer)
{
    
    TouchController *pRet = new TouchController();
    if (pRet && pRet->initWithLayer(aGameLayer))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool TouchController::initWithLayer(cocos2d::Layer* aGameLayer)
{
    _gameLayer = aGameLayer;

    return true;
}

bool isCoordinateOnLine(float coordinate, float posCoordinate, float size, float anchor) {
    float delta = 50;
    return posCoordinate - size*anchor - delta < coordinate && coordinate < posCoordinate + size - size*anchor + delta;
}

bool isTouchingItem(Vec2 touchPoint, Item* item) {
    Vec2 position = item->getPosition();
    Vec2 anchor = item->getAnchorPoint();
    Size size = item->getContentSize();
    
    return isCoordinateOnLine(touchPoint.x, position.x, size.width, anchor.x) && isCoordinateOnLine(touchPoint.y, position.y, size.height, anchor.y);
    //return (item->getPosition().getDistance(touchPoint) < 100.0f);
}

float calculateAngle(Vec2 pos1, Vec2 pos2) {
    float diffX = pos2.x - pos1.x;
    float diffY = pos2.y - pos1.y;
    
    return CC_RADIANS_TO_DEGREES(atan2(diffY, diffX));//CC_RADIANS_TO_DEGREES(atan2(diffY, diffX));
}

void TouchController::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event) {
    CCLOG("TouchController::onTouchesBegan");
    
    if (touches.size() > 0) {
        Touch* currTouch = touches.front();
        _isItemDetected = false;
       // _startTime = millisecondNow();
        //_startPos = [currTouch locationInView: _gameLayer];
        
        _startPos = currTouch->getLocationInView();
        _startPos = CCDirector::getInstance()->convertToGL(_startPos);
        log("You touched %f, %f", currTouch->getLocationInView().x, currTouch->getLocationInView().y);
    }
}

void TouchController::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event) {
    CCLOG("TouchController::onTouchesMoved");
    
    if ( touches.size() > 0) {
        Touch* currTouch = touches.front();
        //  CGPoint currPoint = [currTouch locationInView: _gameLayer];
        
        // log("You touched %f, %f", currTouch->getLocationInView().x, currTouch->getLocationInView().y);
        Vec2 location = currTouch->getLocationInView();
        location = CCDirector::getInstance()->convertToGL(location);
    //    long currTime = millisecondNow();
        
        
        
        //float angle1 = calculateAngle(currTouch->getPreviousLocation(), location);
        //log("---------------: %f", angle1);
        
    
        if (false) { // distance < 0 no move
            // reset start
            //  break;
        }
    
        if (!_isItemDetected) { // curr touch detect item
            // calculate vector
            //for (  _gameLayer->getChildren();
            Item* frontItem = NULL;
            Vector<Node*> children = _gameLayer->getChildren();
            for (auto iter = children.begin(); iter != children.end(); ++iter)
            {
                auto child = *iter;
                if (!_isItemDetected && dynamic_cast<Item*>(child)) {
                    Item *item = (Item *) child;
                    
                    if (20 < item->getLocalZOrder()) { //TODO: make a global const
                        
                        if(isTouchingItem(location, item)) {
                            log("item detected with z-index: %i", item->getLocalZOrder());
                            log("item detected pos x: %g, y:%f, w:%f, h:%f", item->getPosition().x, item->getPosition().y, item->getContentSize().width, item->getContentSize().height);
                            
                            _isItemDetected = true;
                            /*if (frontItem == NULL || (frontItem != NULL && frontItem->getLocalZOrder() < item->getLocalZOrder())) {
                                frontItem = item;
                            }*/
                            frontItem = item;
                            float angle = calculateAngle(_startPos, location);//currTouch->getPreviousLocation(), location);
                            log("item detected angle: %f", angle);
                            
                            GameController* gameController = ((GameMenu *)_gameLayer)->getGameController();
                            gameController->changeItemPath(frontItem, angle, Vec2(0.8, 0.3));
                        }
                    }
                }
            }
            
            /*if (frontItem != NULL) {
                GameController* gameController = ((GameMenu *)_gameLayer)->getGameController();
                gameController->changeItemPath(frontItem, 0.1f, Vec2(0, 0));
            }*/
        }
    }
}

void TouchController::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event) {
    CCLOG("TouchController::onTouchesEnded");
    
    _startTime = 0;//millisecondNow();
  //  _startPos = Vec2(0,0);
    _moveSpeed = 0;
    _isItemDetected = false;
}

void TouchController::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event::Event *unused_event) {
    CCLOG("TouchController::onTouchesCancelled");
}
