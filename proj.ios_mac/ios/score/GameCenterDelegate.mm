
#import "GameCenterDelegate.h"
#import "RootViewController.h"
//#import "AppSpecificValues.h"
//#include "DBManager.h"
#import "AppController.h"

#define kLeaderboardID @"123"

@implementation GameCenterDelegate

@synthesize currentLeaderBoard;

- (id)init {
    self = [super init];
    if (self) {
        self.currentLeaderBoard = kLeaderboardID;
        mViewController = [[[UIApplication sharedApplication] delegate] viewController];
    }

    return self;
}


- (IBAction)showLeaderboard {
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != NULL) {
        leaderboardController.category = self.currentLeaderBoard;
        leaderboardController.timeScope = GKLeaderboardTimeScopeWeek;
        leaderboardController.leaderboardDelegate = self;
        [mViewController presentModalViewController:leaderboardController animated:YES];
    }
}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController {
    [mViewController dismissModalViewControllerAnimated:YES];
    [viewController release];
}


- (IBAction)showAchievements {
    GKAchievementViewController *achievements = [[GKAchievementViewController alloc] init];
    if (achievements != NULL) {
        achievements.achievementDelegate = self;
        [mViewController presentModalViewController:achievements animated:YES];
    }
}

- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController; {
    [mViewController dismissModalViewControllerAnimated:YES];
    [viewController release];
}

- (void)reportByScore {
    if ([GameCenterManager isGameCenterAvailable]) {
        NSUInteger score = 12;
        //TODO: NSUInteger score = (NSUInteger) DBManager::openedCount();
        if (score != 0) {
            [[GameCenterManager instance] reportScore:(int64_t) score forCategory:kLeaderboardID];
        }
    }
}

- (void)scoreReported:(NSError *)error {
    if (error != nil) {
        NSLog(@"descriptions error: %@", error);
    }
}

- (void)achievementSubmitted:(GKAchievement *)ach error:(NSError *)error {
    if ((error == NULL) && (ach != NULL)) {
        // grab an achievement description from where ever you saved them
        [GKAchievementDescription loadAchievementDescriptionsWithCompletionHandler:^(NSArray *descriptions, NSError *err) {
            if (error != nil) {
                // handle errors
                NSLog(@"descriptions error: %@", err);
            }
            if (descriptions != nil) {
                // Run through the descriptions array to find our achievement
                for (GKAchievementDescription *achievementDesc in descriptions) {
                    // Compare IDs
                    if (ach.completed) {
                        if ([ach.identifier isEqualToString:achievementDesc.identifier]) {
                            NSString *description = [achievementDesc description];
                            NSArray *components = [description componentsSeparatedByString:@"\t"];
                            NSString *value = [components objectAtIndex:([components count] - 1)];
                            // Send notification
                            [GKNotificationBanner showBannerWithTitle:[achievementDesc title] message:value completionHandler:nil];
                            break;
                        }
                    }
                }
            }
        }];
    }
}

- (void)dealloc {
    [currentLeaderBoard release];
    [super dealloc];
}

@end