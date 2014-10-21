
#import "InAppPurchaseController.h"
#import "Reachability.h"


@implementation InAppPurchaseController

@synthesize delegate;
@synthesize purchaseId;

- (id)initWithDelegate:(id <InAppPurchaseControllerDelegate>)pDelegate {
    self = [super init];
    if (self) {
        [self setDelegate:pDelegate];
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }

    return self;

}

- (void)loadProductsInfo {
    [delegate startPurchase];
    BOOL isConnection = NO;
    Reachability *internetReach = [Reachability reachabilityForInternetConnection];
    if (internetReach != NULL) {
        NetworkStatus netStatus = [internetReach currentReachabilityStatus];
        if (!(netStatus == NotReachable)) {
            isConnection = YES;
        }
    }
    if (isConnection) {
        SKProductsRequest *request = [[[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:purchaseId]] autorelease];
        [request setDelegate:self];
        [request start];
    } else {
        [delegate purchaseController:self didFailLoadProductInfo:[NSError errorWithDomain:@"internetDomain" code:1
                                                                                 userInfo:[NSDictionary dictionaryWithObject:@"No internet connection."
                                                                                                                      forKey:NSLocalizedDescriptionKey]]];
    }
}

- (void)makePurchase:(SKProduct *)pProduct {
    if (![SKPaymentQueue canMakePayments]) {
        [delegate purchaseController:self didFailPaymentTransactionWithError:[NSError errorWithDomain:@"paymentDomain" code:2
                                                                                             userInfo:[NSDictionary dictionaryWithObject:@"You can not make paiments."
                                                                                                                                  forKey:NSLocalizedDescriptionKey]]];
    } else {
        SKPayment *payment = [SKPayment paymentWithProduct:pProduct];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
}

- (void)restorePurchases {
    if (![SKPaymentQueue canMakePayments]) {
        [delegate purchaseController:self didFailPaymentTransactionWithError:[NSError errorWithDomain:@"paymentDomain" code:2
                                                                                             userInfo:[NSDictionary dictionaryWithObject:@"You can not make paiments."
                                                                                                                                  forKey:NSLocalizedDescriptionKey]]];
    } else {
        [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    }
}

- (BOOL)isPresentNonFinishedTransaction {
    NSArray *arrTransactions = [[SKPaymentQueue defaultQueue] transactions];
    for (SKPaymentTransaction *transaction in arrTransactions) {
        if ([transaction.payment.productIdentifier isEqualToString:purchaseId]) {
            if (transaction.transactionState == SKPaymentTransactionStatePurchasing) {
                return YES;
            } else if (transaction.transactionState == SKPaymentTransactionStateFailed) {
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
            }
        }
    }

    return NO;
}

#pragma mark ---------------request delegate-----------------

- (void)requestDidFinish:(SKRequest *)pRequest {
}

- (void)productsRequest:(SKProductsRequest *)pRequest didReceiveResponse:(SKProductsResponse *)pResponse {
    NSArray *invalidIdentifiers = [pResponse invalidProductIdentifiers];
    NSArray *products = [pResponse products];
    for (SKProduct *product in products) {
        NSString *strId = product.productIdentifier;
        if ([strId isEqualToString:purchaseId]) {
            [delegate purchaseController:self didLoadInfo:product];
            [self makePurchase:product];
            return;
        }
    }
    if ([invalidIdentifiers count]) {
        [delegate purchaseController:self didFailLoadProductInfo:[NSError errorWithDomain:@"purchaseDomain" code:3
                                                                                 userInfo:[NSDictionary dictionaryWithObject:@"No Products found."
                                                                                                                      forKey:NSLocalizedDescriptionKey]]];

    }

}

#pragma mark -------------------transaction observer-------------------

- (void)request:(SKRequest *)pRequest didFailWithError:(NSError *)pError {
    [delegate purchaseController:self didFailPaymentTransactionWithError:pError];
}

- (void)paymentQueue:(SKPaymentQueue *)pQueue updatedTransactions:(NSArray *)pTransactions {
    NSUInteger countTr = [pTransactions count];
    for (NSUInteger i = 0; i < countTr; i++) {
        SKPaymentTransaction *transaction = [pTransactions objectAtIndex:i];
        if (transaction.transactionState == SKPaymentTransactionStatePurchased) {
            [delegate purchaseController:self didFinishPaymentTransaction:transaction count:countTr index:i];
            [pQueue finishTransaction:transaction];
        } else if (transaction.transactionState == SKPaymentTransactionStateRestored) {
            [delegate purchaseController:self didFinishPaymentTransaction:transaction count:countTr index:i];
            [pQueue finishTransaction:transaction];
        } else if (transaction.transactionState == SKPaymentTransactionStateFailed) {
            [delegate purchaseController:self didFailPaymentTransactionWithError:[NSError errorWithDomain:@"purchaseDomain" code:4 userInfo:NULL]];
            [pQueue finishTransaction:transaction];
        }
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions {
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    [delegate purchaseController:self didFailPaymentTransactionWithError:[NSError errorWithDomain:@"purchaseDomain" code:5 userInfo:NULL]];
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    [delegate purchaseController:self didFailPaymentTransactionWithError:[NSError errorWithDomain:@"purchaseDomain" code:6 userInfo:NULL]];
}

- (void)dealloc {
    [purchaseId release];
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [delegate release];
    [super dealloc];
}

@end