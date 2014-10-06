
#import <Foundation/Foundation.h>

@interface PurchaseManager : NSObject<UIAlertViewDelegate>

+ (void)confirmRemoveAds;

+ (void)startPurchase:(NSString *)key;

+ (void)purchaseLives:(int)pCurrentLivesCount;

+ (void)purchaseBonus;

@end