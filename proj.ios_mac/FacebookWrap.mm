
#include "FacebookWrap.h"
#import <FacebookSDK/FacebookSDK.h>

void FacebookWrap::share(const std::string& msg, iOSBridge::Callbacks::FacebookCallBack* callback) {
    NSString *msg1 = [NSString stringWithCString:msg.c_str() encoding:[NSString defaultCStringEncoding]];
     [FBSession.activeSession closeAndClearTokenInformation];
    
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
                                       @"828436257174750",  @"app_id",
                                       @"Sharing Tutorial", @"name",
                                       @"Build great social apps and get more installs.", @"caption",
                                       @"Allow your users to share stories on Facebook from your app using the iOS SDK.", @"description",
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
    
    
    
    callback->complete();
    NSLog(@",.... sended msg %@", msg1);
};

