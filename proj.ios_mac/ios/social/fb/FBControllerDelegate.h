
#import <Foundation/Foundation.h>

@class FBController;

@protocol FBControllerDelegate <NSObject>

- (void)onScoresReceived:(NSMutableDictionary *) res;

- (void)onError;

@end
