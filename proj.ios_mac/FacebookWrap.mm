
#include "FacebookWrap.h"
#import <FacebookSDK/FacebookSDK.h>


FacebookWrap::FacebookWrap() {
    
}
FacebookWrap::~FacebookWrap() {}


void FacebookWrap::share(const std::string& msg, iOSBridge::Callbacks::FacebookCallBack* callback) {
    if (!FBSession.activeSession.isOpen)
        
        [FBSession.activeSession openWithCompletionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
            if (error) {
                this->initSession();
            } else {
                this->doShare(msg);
            }
        }];
    
    
    else  {
        this->doShare(msg);
    }
}

void FacebookWrap::doShare(const std::string& msg) {
    
   NSString *msg1 = [NSString stringWithCString:msg.c_str() encoding:[NSString defaultCStringEncoding]];
 //    [FBSession.activeSession closeAndClearTokenInformation];
    
    // Check if the Facebook app is installed and we can present the share dialog
    FBLinkShareParams *params1 = [[FBLinkShareParams alloc] init];
    params1.link = [NSURL URLWithString:@"https://developers.facebook.com/docs/ios/share/"];
    
    // If the Facebook app is installed and we can present the share dialog
    if ([FBDialogs canPresentShareDialogWithParams:params1]) {
        // Present share dialog
        [FBDialogs presentShareDialogWithLink:params1.link
                                      handler:^(FBAppCall *call, NSDictionary *results, NSError *error) {
                                          if(error) {
                                              // An error occurred, we need to handle the error
                                              // See: https://developers.facebook.com/docs/ios/errors
                                              NSLog(@"Error publishing story: %@", error.description);
                                          } else {
                                              // Success
                                              NSLog(@"result %@", results);
                                          }
                                      }];
    } else {
        // Present the feed dialog
        // Put together the dialog parameters
        NSMutableDictionary *params = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                       //@"828436257174750",  @"app_id",
                                       @"App name", @"name",
                                       @"My current score result.", @"caption",
                                       @"See, my best score reuslt is 39999 points.", @"description",
                                       @"https://developers.facebook.com/docs/ios/share/", @"link",
                                       @"http://i.imgur.com/g3Qc1HN.png", @"picture",
                                       nil];
        
        // Show the feed dialog
        [FBWebDialogs presentFeedDialogModallyWithSession:nil
                                               parameters:params
                                                  handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
                                                      if (error) {
                                                          // An error occurred, we need to handle the error
                                                          // See: https://developers.facebook.com/docs/ios/errors
                                                          NSLog(@"Error publishing story: %@", error.description);
                                                      } else {
                                                          if (result == FBWebDialogResultDialogNotCompleted) {
                                                              // User cancelled.
                                                              NSLog(@"User cancelled.");
                                                          } else {
                                                              // Handle the publish feed callback
                                                              
                                                              NSArray *pairs = [[resultURL query] componentsSeparatedByString:@"&"];
                                                              NSMutableDictionary *urlParams = [[NSMutableDictionary alloc] init];
                                                              for (NSString *pair in pairs) {
                                                                  NSArray *kv = [pair componentsSeparatedByString:@"="];
                                                                  NSString *val =
                                                                  [kv[1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                                                                  params[kv[0]] = val;
                                                              }
                                                              
                                                              
                                                              if (![urlParams valueForKey:@"post_id"]) {
                                                                  // User cancelled.
                                                                  NSLog(@"User cancelled.");
                                                                  
                                                              } else {
                                                                  // User clicked the Share button
                                                                  NSString *result = [NSString stringWithFormat: @"Posted story, id: %@", [urlParams valueForKey:@"post_id"]];
                                                                  NSLog(@"result %@", result);
                                                              }
                                                          }
                                                      }
                                                  }];
    }
    


    NSLog(@",.... sended msg %@", msg1);
   
   
};

void FacebookWrap::postScore(int score, iOSBridge::Callbacks::FacebookCallBack* callback) {

    if (!FBSession.activeSession.isOpen)
        
        [FBSession.activeSession openWithCompletionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
            if (error) {
                this->initSession();
            } else {
                this->doPostScore(score);
            }
        }];
    
    
    else  {
        this->doPostScore(score);
    }
}

void FacebookWrap::doPostScore(int nScore) {
    [FBRequestConnection startWithGraphPath:@"/me/scores"
                                 parameters:nil
                                 HTTPMethod:@"GET"
                          completionHandler:^(
                                              FBRequestConnection *connection,
                                              id result,
                                              NSError *error
                                              ) {
                              
                              if (result && !error) {
                                  
                                  int nCurrentScore = 0;
                                  if ([[result objectForKey:@"data"] count] > 0)
                                      
                                      
                                      nCurrentScore = [[[[result objectForKey:@"data"] objectAtIndex:0] objectForKey:@"score"] intValue];
                                  
                                  NSLog(@"Current score is %d", nCurrentScore);
                                  
                                  if (nScore > nCurrentScore) {
                                      
                                      NSLog(@"Posting new score of %d", nScore);
                                      NSMutableDictionary* params =   [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                                       [NSString stringWithFormat:@"%d", nScore], @"score",
                                                                       nil];
                                      
                                      [FBRequestConnection startWithGraphPath:@"me/scores"
                                                                   parameters:params
                                                                   HTTPMethod:@"POST"
                                                            completionHandler:
                                       ^(FBRequestConnection *connection, id result, NSError *error) {
                                           
                                           NSLog(@"Score posted");
                                       }];
                                  }
                                  else {
                                      NSLog(@"Existing score is higher - not posting new score");
                                  }
                              }
                          }];
}

void FacebookWrap::readGlobalScores(iOSBridge::Callbacks::FacebookCallBack* callback) {
    
    /*auto readHandler = [=] (EventCustom *e){
        
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("FACEBOOK_LOGIN");
        
        this->doReadGlobalScores();
    };
    auto listener = EventListenerCustom::create("FACEBOOK_LOGIN", readHandler);
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listener, 1);// addCustomEventListener("FACEBOOK_LOGIN", readHandler);*/
    
    if (!FBSession.activeSession.isOpen)
        
        [FBSession.activeSession openWithCompletionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
            if (error) {
                this->initSession();
            } else {
                this->doReadGlobalScores();
            }
        }];
        
        
    else  {
        this->doReadGlobalScores();
    }
}

void FacebookWrap::doReadGlobalScores() {
    
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
                                          for (id data : [result objectForKey:@"data"]) {
                                              int score = [[data objectForKey:@"score"] intValue];
                                              NSLog(@"score");
                                              id user = [data objectForKey:@"user"];
                                              NSString* name = [user objectForKey:@"name"];
                                              //NSString* userId = [user objectForKey:@"id"];
                                              
                                              
                                              NSLog(@"User: %@ - score: %i", name, score);
                                          }
                                      }
                                  }
                                  
                              }];
}


bool FacebookWrap::initSession() {
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
                                                     
                                                     
                                                     EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
                                                     dispatcher->dispatchCustomEvent("FACEBOOK_LOGIN");
                                                     
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
                                             
                                             //[[NSNotificationCenter defaultCenter]
                                             // postNotificationName:FBSessionStateChangedNotification
                                             // object:session];
                                             
                                             if (error) {
                                                 NSLog(@"Facebook Error %@", error);
                                             }
                                         }];

}



