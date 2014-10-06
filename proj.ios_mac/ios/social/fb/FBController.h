
#import <Foundation/Foundation.h>


@protocol FBControllerDelegate;


@interface FBController : NSObject

@property(retain, readwrite) id <FBControllerDelegate> delegate;

- (id)initWithDelegate:(id <FBControllerDelegate>)pDelegate;

- (void) getScoreList;

- (void) postScore:(int) score;

@end
