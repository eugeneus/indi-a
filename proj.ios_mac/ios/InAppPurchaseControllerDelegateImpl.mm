
#import "InAppPurchaseControllerDelegateImpl.h"
#import "InAppPurchaseController.h"
#import "RootViewController.h"
#import "PurchaseManager.h"

USING_NS_CC;

@implementation InAppPurchaseControllerDelegateImpl

//@synthesize isRestoredTransaction;


- (void)startPurchase {
    //Director::getInstance()->getEventDispatcher()-> pauseEventListenersForTarget(<#cocos2d::Node *target#>)  g etTouchDispatcher()->setDispatchEvents(false);
}

- (void)purchaseController:(InAppPurchaseController *)pController didLoadInfo:(SKProduct *)pProduct {
    mController = pController;
}

- (void)purchaseController:(InAppPurchaseController *)pController didFailLoadProductInfo:(NSError *)pError {
    
}

- (void)purchaseController:(InAppPurchaseController *)pController didFinishPaymentTransaction:(SKPaymentTransaction *)pTransaction count:(int)pCount index:(int)pIndex {
}

- (void)purchaseController:(InAppPurchaseController *)pController didFailPaymentTransactionWithError:(NSError *)pError {
    if ([pError description] != NULL) {
        //NSLog([pError description]);
    }
    [self endPurchase];
}

- (void)endPurchase {
    //CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
}


@end
