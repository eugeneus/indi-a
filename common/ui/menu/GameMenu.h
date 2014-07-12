
#ifndef __BlindChef__GameMenu__
#define __BlindChef__GameMenu__

#include "cocos2d.h"
#include "SimpleMenu.h"

class MovementController;
class GameController;

class GameMenu : public SimpleMenu
{
private:
    typedef SimpleMenu super;
   
    GameController* _theGameController;
    MovementController* _mover;
   
protected:
    void update(float dt);
public:
    static GameMenu* create();
    static cocos2d::Scene* createScene();
    virtual void initializeMenu();
    //virtual void draw();
   virtual void draw(cocos2d::Renderer* renderer, const cocos2d::kmMat4& transform, bool transformUpdated);
};


#endif /* defined(__BlindChef__GameMenu__) */
