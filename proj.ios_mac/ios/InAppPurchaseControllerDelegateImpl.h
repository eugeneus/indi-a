

#import <Foundation/Foundation.h>
#include "cocos2d.h"

@protocol InAppPurchaseControllerDelegate;
@class InAppPurchaseController;

@interface InAppPurchaseControllerDelegateImpl : NSObject  <InAppPurchaseControllerDelegate>
{
    BOOL isRestoredTransaction;
    InAppPurchaseController *mController;
}
@end
