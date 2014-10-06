
#import "FBManager.h"
#import "FBController.h"
#import "FBControllerDelegateImpl.h"

@implementation FBManager

static FBController *fbController;

+ (void) initController {
    if (fbController == NULL) {
        FBControllerDelegateImpl *delegate = [[[FBControllerDelegateImpl alloc] init] autorelease];
        fbController = [[FBController alloc] initWithDelegate:delegate];
    }
}

+ (void)getScoreList {
    [self initController];
    [fbController getScoreList];
}

+ (void)postBestResult:(int) result {
    [self initController];
    [fbController postScore:result];
}

@end
