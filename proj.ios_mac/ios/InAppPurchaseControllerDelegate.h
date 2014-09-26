
#import <Foundation/Foundation.h>

@class SKPaymentTransaction;
@class SKProduct;
@class InAppPurchaseController;

@protocol InAppPurchaseControllerDelegate <NSObject>


- (void)startPurchase;

- (void)endPurchase;

- (void)purchaseController:(InAppPurchaseController *)pController didLoadInfo:(SKProduct *)pProduct;

- (void)purchaseController:(InAppPurchaseController *)pController didFailLoadProductInfo:(NSError *)pError;

- (void)purchaseController:(InAppPurchaseController *)pController didFinishPaymentTransaction:(SKPaymentTransaction *)pTransaction count:(int)pCount index:(int)pIndex;

- (void)purchaseController:(InAppPurchaseController *)pController didFailPaymentTransactionWithError:(NSError *)pError;

- (void)purchaseController:(InAppPurchaseController *)pController paymentQueueRestoreCompletedTransactionsFinished:(NSError *)pError;

@end
