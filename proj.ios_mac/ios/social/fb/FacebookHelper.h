#include <iostream>
#include <vector>
#import <FacebookSDK/FacebookSDK.h>
#import "FBHDelegate.h"
#import "FBHWrapperCpp.h"

@protocol FacebookHelperProtocol

-(void) onScoresReceived:(NSArray*)scores;

@end


@interface FacebookHelper : NSObject
{
	id<FacebookHelperProtocol> delegate;
	NSError* lastError;
}

//@property (nonatomic, retain) id<GameKitHelperProtocol> delegate;
@property (nonatomic, readonly) NSError* lastError;

/** returns the singleton object, like this: [GameKitHelper sharedGameKitHelper] */
+(FacebookHelper*) sharedHelper;

-(void) retrieveTopTenAllTimeGlobalScoresForCatagory:(NSString*)catagory;
//delegate
-(void)setDelegate:(FBHDelegate*) fbDelegate;


//C++/Objective-C type converters

@end