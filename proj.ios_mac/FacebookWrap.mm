
#include "FacebookWrap.h"
#import <FacebookSDK/FacebookSDK.h>

void FacebookWrap::share(const std::string& msg, iOSBridge::Callbacks::FacebookCallBack* callback) {
    NSString *msg1 = [NSString stringWithCString:msg.c_str() encoding:[NSString defaultCStringEncoding]];
    
    [FBRequest requestForMyFriends];

    //FBLoginView* view = [[FBLoginView alloc] init];
    //view //[self.s]

    
     //cocos2d::Director::getInstance()->getr
   // FBSession* session = [FBSession activeSession];
   // FBRequest* request = [FBRequest requestForMe];
   // [request parameters]
    
    /* FBLinkShareParams *params = [[FBLinkShareParams alloc] init];
    params.link = [NSURL URLWithString:@"https://developers.facebook.com/docs/ios/share/"];
    
    // If the Facebook app is installed and we can present the share dialog
    if ([FBDialogs canPresentShareDialogWithParams:params]) {
        // Present the share dialog
        [FBDialogs presentShareDialogWithLink:params.link
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
        BOOL opened = [FBSession openActiveSessionWithAllowLoginUI:NO];
        // Present the feed dialog
        NSLog(@"present feed dialog %@", opened ? @"yes" : @"no");
    }*/
    callback->complete();
    NSLog(@",.... sended msg %@", msg1);
};