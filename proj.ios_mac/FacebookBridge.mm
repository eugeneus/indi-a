#import "FacebookBridge.h"

@implementation FacebookBridge

// cocos2d application instance
static FacebookBridge s_sharedApplication;


(FacebookBridge*) getInstance {
    if (! s_sharedApplication) {
        s_sharedApplication = new FacebookBridge();
    }
    return s_gc;
}


void share{
    AppController* app = (AppController*)[[UIApplication sharedApplication] delegate];
    [app shareFb:@"blabla"];
}