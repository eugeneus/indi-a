
#include "Item.h"

USING_NS_CC;

bool Item::init(string spriteFrameName, const char* framesPattern, int spriteCount, float deleayTime) {
    
    if(!super::initWithSpriteAndPos(spriteFrameName, framesPattern, spriteCount, deleayTime)) {
        return false;
    }
   
   _defaultScale = 1.0;
    _itemType = -1;
    _itemId = -1;
   
   _bumpSoundFileName = "item_fall.caf";

 /*
   DrawNode *dotNode = DrawNode::create();
   dotNode->drawDot(this->getPosition(), 5, Color4F(Color3B::WHITE));
   this->addChild(dotNode);
*/
   /*
   Rect r1 = Node::getRect();
   DrawNode *dotNode1 = DrawNode::create();
   Point p1 = r1.origin;
   p1.x += r1.size.width;
   Point p2 = p1;
   p2.y += r1.size.height;
   Point p3 = p2;
   p3.x = r1.origin.x;
   Point verts [] = {r1.origin,p1,p2,p3};
   dotNode1->drawPolygon(verts, 4, Color4F(1,222,120,0.2), 1.0, Color4F(Color3B::WHITE));
   */
    
    return true;
}

// based on predefined end points
ccBezierConfig Item::bezierConfigBouncePathToEndPoint(Point anEndPoint, Vec2 anImpulse)
{
   ccBezierConfig bezier;
   Size visibleSize = Size(Director::getInstance()->getVisibleSize());
   Point itemPos = this->getPosition();
   Point cp1 = itemPos;
   
   // assume start point of impulse always (0,0)
   cp1.y = itemPos.y + ((visibleSize.height) * anImpulse.y);
   cp1.x = itemPos.x + ((anEndPoint.x - itemPos.x) * anImpulse.x);
   
   bezier.controlPoint_1 = cp1;
   bezier.controlPoint_2 = anEndPoint;
   bezier.endPosition = anEndPoint;
   
   return bezier;
   
}

// based on predefined end points
ccBezierConfig Item::bezierConfigTouchPathToEndPoint(Point anEndPoint, Vec2 anImpulse)
{
    ccBezierConfig bezier;
    Size visibleSize = Size(Director::getInstance()->getVisibleSize());
    Point itemPos = this->getPosition();
    Point cp1 = itemPos;
    
    // assume start point of impulse always (0,0)
    cp1.y = itemPos.y + ((visibleSize.height) * anImpulse.y);
    cp1.x = itemPos.x + ((anEndPoint.x - itemPos.x) * anImpulse.x);
    
    bezier.controlPoint_1 = cp1;
    bezier.controlPoint_2 = anEndPoint;
    bezier.endPosition = anEndPoint;
    
    return bezier;
    
}

cocos2d::FiniteTimeAction* Item::getConveyourAction(float aDuration, cocos2d::Point anEndPoint)
{

   this->_currentTargetPoint = anEndPoint;
   this->_currentTargetType = 0;
   
   FiniteTimeAction* actionMove = MoveTo::create(aDuration,anEndPoint);
   // add action to
   actionMove->setTag(1001);
   
   return actionMove;
   
}


cocos2d::FiniteTimeAction* Item::getTossAction(float aDuration, cocos2d::Point anEndPoint,
                                               int aCollisionType, cocos2d::Point anImpulse)
{
   this->stopActionByTag(1001);
   
   this->_currentTargetPoint = anEndPoint;
   this->_currentTargetType = aCollisionType;
   
   ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(anEndPoint, anImpulse);
   BezierTo* bezierBounceAction = BezierTo::create(aDuration, bouncePathConfig);
   
   RotateTo* r1 = RotateTo::create(aDuration/9.0f, 120.0f);
   RotateTo* r2 = RotateTo::create(aDuration/9.0f, 240.0f);
   RotateTo* r3 = RotateTo::create(aDuration/9.0f, 360.0f);
   
   Sequence* rt = Sequence::create(r1, r2, r3, NULL);
   Repeat* repeated = Repeat::create(rt, 3);

   FiniteTimeAction* fullAction = NULL;
   fullAction =  Sequence::create(bezierBounceAction,
                                  NULL);
   
   FiniteTimeAction* combinedAction = Spawn::create(fullAction, repeated, NULL);
   
   return combinedAction;
   
}

cocos2d::FiniteTimeAction* Item::getPotEdgeBumpAction(float aDuration, cocos2d::Point anImpulse)
{
   
   // 1 next EndPoint calc
   Point currentPoint = this->getPosition();
   
   float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
   _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
   _currentTargetType = 1; // fall on floor
   // calc path
   ccBezierConfig bouncePathConfig = this->bezierConfigBouncePathToEndPoint(_currentTargetPoint, anImpulse);
   FiniteTimeAction* moveAction = BezierTo::create(aDuration, bouncePathConfig);

   RotateTo* r1 = RotateTo::create(aDuration/12.0f, 120.0f);
   RotateTo* r2 = RotateTo::create(aDuration/12.0f, 240.0f);
   RotateTo* r3 = RotateTo::create(aDuration/12.0f, 360.0f);
   
   Sequence* rt = Sequence::create(r1, r2, r3, NULL);
   Repeat* repeatedRotation = Repeat::create(rt, 4);
   
   FiniteTimeAction* combinedAction = Spawn::create(moveAction, repeatedRotation, NULL);
   
   return combinedAction;
}

cocos2d::FiniteTimeAction* Item::getFloorBumpAction(float aDuration, cocos2d::Point anImpulse)
{
   
   Point currentPoint = this->getPosition();
   
   float direction = currentPoint.x > 320.0f ? 1.0f : -1.0f;
   _currentTargetPoint = Point(currentPoint.x + (100.0f * anImpulse.x * direction), currentPoint.y - (50.0f * anImpulse.y));
   _currentTargetType = 1;
   // calc path
   float jumpHeight = (50.0f * anImpulse.y);
   int jumpsCount = 2;
   FiniteTimeAction* jumpAction = JumpTo::create(aDuration, _currentTargetPoint, jumpHeight, jumpsCount);

   RotateTo* r1 = RotateTo::create(aDuration/6.0f, 60.0f);
   RotateTo* r2 = RotateTo::create(aDuration/6.0f, 0.0f);
   Sequence* rt = Sequence::create(r1, r2, NULL);

   Repeat* repeatedRotation = Repeat::create(rt, 2);

   FiniteTimeAction* combinedAction = Spawn::create(jumpAction, repeatedRotation, NULL);
   
   return combinedAction;
   
}

void Item::runCatchAction(float aDuration, cocos2d::Point anEndPoint)
{
   this->stopActionByTag(1001);
   MoveTo* moveUp = MoveTo::create(aDuration, anEndPoint);
   this->runAction(moveUp);
}

cocos2d::FiniteTimeAction* Item::getFingerKickAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse)
{
   
   return nullptr;
   
}

cocos2d::FiniteTimeAction* Item::getVanishAction(float aDuration, cocos2d::Point anEndPoint, cocos2d::Point anImpulse)
{
   
   _currentTargetPoint = _idleItemPosition;
   _currentTargetType = 0;
   
   //FiniteTimeAction* actionDelay = DelayTime::create(2);
   FiniteTimeAction* actionPlase = Place::create(_idleItemPosition);
   FiniteTimeAction* actionFadeOut = FadeOut::create(2);
   FiniteTimeAction* actionFadeIn = FadeIn::create(2);
   
   FiniteTimeAction* fullAction = Sequence::create(actionFadeOut, //actionDelay,
                                                   actionPlase,
                                                   actionFadeIn,
                                                   NULL);

   return fullAction;
   
}

bool Item::isItemInCurrentTargetPoint()
{
   Point currPos = this->getPosition();
   
   return _currentTargetPoint.equals(this->getPosition());

}

void Item::setIdle(cocos2d::Point anIdleItemPosition)
{
   this->_idleItemPosition = anIdleItemPosition;
   this->setPosition(_idleItemPosition);
   this->stopAllActions();
   this->setDefaultSize();
   this->setOpacity(255);
   this->setRotation(0);
   
}

void Item::stopActions()
{
   this->stopAllActions();
   this->setDefaultSize();
   
}

void Item::playBumpSound()
{
   CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(this->_bumpSoundFileName.c_str(), false);

}

Sprite* Item::createCrack() {
    return NULL;
}



