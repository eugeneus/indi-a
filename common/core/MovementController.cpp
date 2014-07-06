
#include "MovementController.h"
#include "Item.h"


MovementController::MovementController(){}

MovementController::~MovementController() {}

MovementController* MovementController::create() {

   return new MovementController();
}

bool MovementController::init()
{
   cocos2d::Size visibleSize;
   visibleSize = Director::getInstance()->getVisibleSize();
   _grabPosX = visibleSize.width / 2.0f + 40.0f;
   createFallenPathArray();
   return true;
}

BezierTo* MovementController::createBezierPath(Vec2 aStartPos)
{
   ccBezierConfig bezier;
   
   // Bezier curve
   cocos2d::Size visibleSize;
   visibleSize = Director::getInstance()->getVisibleSize();
   
   
   bezier.controlPoint_1 = Vec2(aStartPos.x,aStartPos.y);
   bezier.controlPoint_2 = Vec2(aStartPos.x - 40, visibleSize.height / 2.0f);
   bezier.endPosition = Vec2(aStartPos.x + 60,-visibleSize.height/ 2.0f);
   
   return BezierTo::create(10, bezier);

}

void MovementController::createFallenPathArray()
{
   
   ccBezierConfig bezier;
   
   // Bezier curve
   cocos2d::Size visibleSize;
   visibleSize = Director::getInstance()->getVisibleSize();
   

   bezier.controlPoint_1 = Vec2(_grabPosX,475.0f);
   bezier.controlPoint_2 = Vec2(_grabPosX+20, visibleSize.height / 2.0f - 60);
   bezier.endPosition = Vec2(_grabPosX + 40,visibleSize.height);
   
   BezierTo* bezierBy1 = BezierTo::create(10, bezier);
                                  
   //CCBezierTo to = CCBezierTo.action(2, bezier);
   
   //CCCallFuncN actionMoveDone = CCCallFuncN.action(this,"spriteMoveFinished");
   //CCSequence actions = CCSequence.actions(by, actionMoveDone);
   
   //obstacle1.runAction(actions);
   
   //cocos2d::Action* =
   _pathActions.pushBack(bezierBy1);

}

void MovementController::addItem(Item& anItem)
{
   _items.pushBack(&anItem);
}

void MovementController::processThrowAction()
{
   for(int i=0;i<_items.size();i++)
	{
		auto item = _items.at(i);
      Vec2 pos = item->getPosition();
      if (pos.x > _grabPosX - 40 && pos.x < _grabPosX) {
         
         item->runAction(this->createBezierPath(pos));
         
      }
		
	}
}

void MovementController::update(float dt)
{
   
   this->processThrowAction();

}

