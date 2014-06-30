
#include "Conveyor.h"

USING_NS_CC;

Conveyor* Conveyor::create()
{
    Conveyor *pRet = new Conveyor();
    if (pRet && pRet->init())
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

Scene* Conveyor::createScene()
{
    auto scene = Scene::create();
    auto layer = Conveyor::create();
    scene->addChild(layer);
    return scene;
}

bool Conveyor::init() {
    
    if(!super::init("conveyer_1.png", 400, 640)) {
        return false;
    }
    
    
    return true;
}