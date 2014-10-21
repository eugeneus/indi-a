
#import "InAppPurchaseControllerDelegateImpl.h"
#import "InAppPurchaseController.h"
#import "RootViewController.h"
#import "PurchaseManager.h"

USING_NS_CC;

@implementation InAppPurchaseControllerDelegateImpl

//@synthesize isRestoredTransaction;


- (void)startPurchase {
    //Director::getInstance()->getEventDispatcher()-> pauseEventListenersForTarget(<#cocos2d::Node *target#>)  g etTouchDispatcher()->setDispatchEvents(false);
    Director::getInstance()->pause();
    /*ActivityIndicator
    
    
    UIActivityIndicatorView *spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    spinner.color = [UIColor orangeColor];
    spinner.hidesWhenStopped = YES;
    Director::getInstance()->getView()->addSubview(spinner);// ->getOpenGLView()->addSubview(spinner);
    [spinner startAnimating];*/
}

- (void)purchaseController:(InAppPurchaseController *)pController didLoadInfo:(SKProduct *)pProduct {
    mController = pController;

    //[self endPurchase];
}

- (void)purchaseController:(InAppPurchaseController *)pController didFailLoadProductInfo:(NSError *)pError {
    [self endPurchase];
}

- (void)purchaseController:(InAppPurchaseController *)pController didFinishPaymentTransaction:(SKPaymentTransaction *)pTransaction count:(int)pCount index:(int)pIndex {
    [self endPurchase];
}

- (void)purchaseController:(InAppPurchaseController *)pController didFailPaymentTransactionWithError:(NSError *)pError {
    if ([pError description] != NULL) {
        //NSLog([pError description]);
    }
    [self endPurchase];
}

- (void)endPurchase {
    //CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
    Director::getInstance()->resume();
}


@end
