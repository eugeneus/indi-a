
#ifndef __BlindChef__GameController__
#define __BlindChef__GameController__


#include "cocos2d.h"
USING_NS_CC;

class GameController {

private:

   cocos2d::Layer* _gameLayer;
   
protected:
   
   void populateBackground();
   
   void populateGameObjects();

public:

   GameController();

   ~GameController();

   static GameController* createWitLayer(cocos2d::Layer* aGameLayer);

   bool initWithLayer(cocos2d::Layer* aGameLayer);
   
   void startGame();
   
   void stopGame();
   
   void update(float dt);


};
#endif /* defined(__BlindChef__GameController__) */
