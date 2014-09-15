//
//  Created by andrew on 16.05.12.
//
//


#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import "GameCenterManager.h"

@class GameCenterManager;
@class RootViewController;


@interface GameCenterDelegate : NSObject <UIActionSheetDelegate, GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GameCenterManagerDelegate> {
    RootViewController *mViewController;
}

@property(nonatomic, retain) NSString *currentLeaderBoard;

- (IBAction)showLeaderboard;

- (IBAction)showAchievements;

- (void)reportByScore;

@end