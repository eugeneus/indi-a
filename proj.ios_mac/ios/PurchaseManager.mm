
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


+ (void)startPurchase:(int)pPurchaseId {
    char const *purchaseKey = "sdf";//SettingsManager::keyById(pPurchaseId)->getCString();
    NSString *key = [[[NSString alloc] initWithUTF8String:purchaseKey] autorelease];
    if (inAppPurchaseController == NULL) {
        InAppPurchaseControllerDelegateImpl *delegate = [[[InAppPurchaseControllerDelegateImpl alloc] init] autorelease];
        inAppPurchaseController = [[InAppPurchaseController alloc] initWithDelegate:delegate];
    }
    [inAppPurchaseController setPurchaseId:key];
    [inAppPurchaseController loadProductsInfo];
}

@end