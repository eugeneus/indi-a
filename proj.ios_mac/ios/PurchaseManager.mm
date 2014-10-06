
#import "PurchaseManager.h"
//#include "SettingsManager.h"
//#import "AdsAdapter.h"
#import "InAppPurchaseController.h"
#import "InAppPurchaseControllerDelegateImpl.h"
//#import "MenuManager.h"
//#import "StartLevelMenu.h"
//#import "GameSceneMenu.h"
//#import "LevelMenu.h"


@implementation PurchaseManager

static InAppPurchaseController *inAppPurchaseController;

+ (void)confirmRemoveAds {
//    if (!SettingsManager::prefsById(settingsAdsShow)) {
//        [AdsAdapter hideAds];
//        MenuManager::updateBottomMenu();
//    }
}

+ (void)purchaseBonus {
    [PurchaseManager startPurchase:@"bc_purchase_bonus"];
}

+ (void)startPurchase:(NSString *)key {
    if (inAppPurchaseController == NULL) {
        InAppPurchaseControllerDelegateImpl *delegate = [[[InAppPurchaseControllerDelegateImpl alloc] init] autorelease];
        inAppPurchaseController = [[InAppPurchaseController alloc] initWithDelegate:delegate];
    }
    [inAppPurchaseController setPurchaseId:key];
    [inAppPurchaseController loadProductsInfo];
}

+ (void)purchaseLives:(int)pCurrentLivesCount {
    if (pCurrentLivesCount < 10) {
        
        [PurchaseManager startPurchase:@"bc_purchase_live"];
        
        /*int toRestore = 10 - pCurrentLivesCount;
        
        UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Restore Lives."
                                                         message:@"Bla bla bla bla bla ."
                                                        delegate:self
                                               cancelButtonTitle:@"Cancel"
                                               otherButtonTitles:nil] autorelease];
        if (toRestore > 1) {
            [alert addButtonWithTitle:@"Buy one"];
            [alert addButtonWithTitle:@"Buy all"];
        } else {
            [alert addButtonWithTitle:@"Buy one"];
        }
        [alert show];
        //[alert release];*/
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex == [alertView cancelButtonIndex]){
        CCLOG("cancel");
    } else if (buttonIndex == 1) {
        CCLOG("one");
    } else if (buttonIndex == 2) {
        CCLOG("all");
    }
}

@end