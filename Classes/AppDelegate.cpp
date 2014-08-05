#include "AppDelegate.h"
#include "MainMenu.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    auto screenSize = glview->getFrameSize();
    
    if (2048 == screenSize.width || 2048 == screenSize.height) {
        log("-- res = 2048");
        glview->setDesignResolutionSize(1536, 2048, ResolutionPolicy::NO_BORDER);
    } else if (1024 == screenSize.width || 1024 == screenSize.height) {
        log("-- res = 1024");
        glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
    } else if (1136 == screenSize.width || 1136 == screenSize.height) {
        log("-- res = 1136");
        glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
    } else if (960 == screenSize.width || 960 == screenSize.height) {
        log("-- res = 960");
        glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
    }

   // glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    
    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
