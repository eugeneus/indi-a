
#import "FBController.h"
#import <FacebookSDK/FacebookSDK.h>
#import "FBControllerDelegate.h"

@implementation FBController
@synthesize delegate;
- (id)initWithDelegate:(id <FBControllerDelegate>)pDelegate {
    self = [super init];
    if (self) {
        [self setDelegate:pDelegate];
    }
    
    return self;
    
}

- (BOOL) doInitSession {
    NSArray *permissions = @[@"publish_actions", @"user_friends", @"user_games_activity", @"friends_games_activity"];
    
    
    return [FBSession openActiveSessionWithReadPermissions:permissions
                                              allowLoginUI:true
                                         completionHandler:^(FBSession *session,
                                                             FBSessionState state,
                                                             NSError *error) {
                                             
                                             switch (state) {
                                                 case FBSessionStateOpen: {
                                                     // We have a valid session
                                                     NSLog(@"User session found");
                                                     if (FBSession.activeSession.isOpen) {
                                                         [FBRequestConnection
                                                          startForMeWithCompletionHandler:^(FBRequestConnection *connection,
                                                                                            id<FBGraphUser> user,
                                                                                            NSError *error) {
                                                              if (!error) {
                                                                  NSLog(@"accessToken: %@ userID: %@",[FBSession activeSession].accessTokenData.accessToken, user.objectID);
                                                                  //  self.userID = user.objectID;
                                                                  [[NSUserDefaults standardUserDefaults] setValue:user.first_name  forKey:@"first_name"];
                                                                  [[NSUserDefaults standardUserDefaults] setValue:user.last_name  forKey:@"last_name"];
                                                                  // NSString *accessToken = [FBSession activeSession].accessTokenData.accessToken;
                                                                  
                                                                  /*  if (accessToken) {
                                                                   [[NSNotificationCenter defaultCenter] postNotificationName:FacebookLoginInProgressNotification object:nil];
                                                                   [self submitFacebookUserID:user.id andAccessToken:accessToken];
                                                                   }
                                                                   else {
                                                                   NSLog(@"no access token for userID: %@",user.id);
                                                                   [[NSNotificationCenter defaultCenter] postNotificationName:FacebookLoginFailureNotification object:nil];
                                                                   }*/
                                                              }
                                                              else {
                                                                  //handle error retrieving User ID
                                                                  NSLog(@"error retrieving User ID [%@]",[error localizedDescription]);
                                                                  // [[NSNotificationCenter defaultCenter] postNotificationName:FacebookLoginFailureNotification object:nil];
                                                              }
                                                          }];
                                                     } else {
                                                         [FBSession setActiveSession:session];
                                                     }
                                                     
                                                     // Pre-fetch and cache the friends for the friend picker as soon as possible to improve
                                                     // responsiveness when the user tags their friends.
                                                     FBCacheDescriptor *cacheDescriptor = [FBFriendPickerViewController cacheDescriptor];
                                                     [cacheDescriptor prefetchAndCacheForSession:session];
                                                 }
                                                     break;
                                                 case FBSessionStateClosed: {
                                                     [FBSession.activeSession closeAndClearTokenInformation];
                                                 }
                                                     break;
                                                 case FBSessionStateClosedLoginFailed: {
                                                     [FBSession.activeSession closeAndClearTokenInformation];
                                                 }
                                                     break;
                                                 default:
                                                     break;
                                             }
                                             
                                             if (error) {
                                                 NSLog(@"Facebook Error %@", error);
                                             }
                                         }];
}

- (void) doGetScoreList {
    [FBRequestConnection startWithGraphPath:@"/1511878459049707/scores"
                                 parameters:nil
                                 HTTPMethod:@"GET"
                          completionHandler:^(
                                              FBRequestConnection *connection,
                                              id result,
                                              NSError *error
                                              ) {
                              
                              
                              if (result && !error) {
                                  NSLog(@"good");
                                  
                                  if ([[result objectForKey:@"data"] count] > 0)  {
                                      [delegate onScoresReceived:[result objectForKey:@"data"]];
                                  } else
                                      [delegate onError];
                              } else {
                                  [delegate onError];
                              }
                          
                          }];
    
}

- (void) getScoreList {

    if (!FBSession.activeSession.isOpen) {
        
        [FBSession.activeSession openWithCompletionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
            if (error) {
                if ([self doInitSession]) {
                    [self doGetScoreList];
                } else {
                    [delegate onError];
                }
            } else {
                [self doGetScoreList];
            }
        }];
    } else  {
        [self doGetScoreList];
    }
    
}

@end
