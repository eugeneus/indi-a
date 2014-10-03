
#import "FBManager.h"
#import "FBController.h"
#import "FBControllerDelegateImpl.h"

@implementation FBManager

static FBController *fbController;

+ (void)getScoreList {
    if (fbController == NULL) {
        FBControllerDelegateImpl *delegate = [[[FBControllerDelegateImpl alloc] init] autorelease];
        fbController = [[FBController alloc] initWithDelegate:delegate];
    }
    [fbController getScoreList];
}

@end
