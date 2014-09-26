
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "InAppPurchaseControllerDelegate.h"

@protocol InAppPurchaseControllerDelegate;


@interface InAppPurchaseController : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>

@property(retain, readwrite) id <InAppPurchaseControllerDelegate> delegate;
@property(copy, readwrite) NSString *purchaseId;

- (id)initWithDelegate:(id <InAppPurchaseControllerDelegate>)pDelegate;

- (void)loadProductsInfo;

- (void)makePurchase:(SKProduct *)pProduct;

- (void)restorePurchases;

- (BOOL)isPresentNonFinishedTransaction;

@end