
#ifndef __BlindChef__GameController__
#define __BlindChef__GameController__

class GameController {

private:

protected:

public:

   GameController();

   ~GameController();

   static GameController* create();

   bool init();
   
   void startGame();
   
   void stopGame();
   
   void update(float dt);


};
#endif /* defined(__BlindChef__GameController__) */
