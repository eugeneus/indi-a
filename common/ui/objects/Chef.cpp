
#include "Chef.h"

USING_NS_CC;

Chef* Chef::create()
{
    Chef *pRet = new Chef();
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

Scene* Chef::createScene()
{
    auto scene = Scene::create();
    auto layer = Chef::create();
    scene->addChild(layer);
    return scene;
}

bool Chef::init() {
    
    if(!super::initWithSpriteAndPos("chef_1.png", "chef_%i.png", 4, 0.9)) {
        return false;
    }
    
    
    return true;
}