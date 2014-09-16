
#include "FacebookHelper.h"
#include "ScoreFBDataSource.h"

@interface FacebookHelper (Private)
-(void) setLastError:(NSError*)error;
@end

@implementation FacebookHelper{
    
    FBHWrapperCpp *_gkhDelegate;
    
}

static FacebookHelper *instanceOfHelper;

#pragma mark Singleton stuff
+(id) alloc
{
	@synchronized(self)
	{
		NSAssert(instanceOfHelper == nil, @"Attempted to allocate a second instance of the singleton: GameKitHelper");
		instanceOfHelper = [[super alloc] retain];
		return instanceOfHelper;
	}
	
	// to avoid compiler warning
	return nil;
}

+(FacebookHelper*) sharedHelper
{
	@synchronized(self)
	{
		if (instanceOfHelper == nil)
		{
			[[FacebookHelper alloc] init];
		}
		
		return instanceOfHelper;
	}
	
	// to avoid compiler warning
	return nil;
}

#pragma mark Init & Dealloc

//@synthesize delegate;

@synthesize lastError;

-(id) init
{
	if ((self = [super init]))
	{
        
        _gkhDelegate = nullptr;
	}
	
	return self;
}

-(void) dealloc
{
	//CCLOG(@"dealloc %@", self);
    
    NSLog(@"dealloc %@", self);
    
	
	[instanceOfHelper release];
	instanceOfHelper = nil;
	
	[lastError release];
	
	[super dealloc];
}

#pragma mark setLastError

-(void) setLastError:(NSError*)error
{
	[lastError release];
	lastError = [error copy];
	
	if (lastError)
	{
		NSLog(@"GameKitHelper ERROR: %@", [[lastError userInfo] description]);
	}
}

-(void) retrieveTopTenAllTimeGlobalScoresForCatagory:(NSString*)catagory
{
    
    __block FBHWrapperCpp* tmpDelegate = _gkhDelegate;//new ScoreFBDataSource(*(ScoreFBDataSource*) _gkhDelegate);
	[FBRequestConnection startWithGraphPath:@"/1511878459049707/scores"
                                 parameters:nil
                                 HTTPMethod:@"GET"
                          completionHandler:^(
                                              FBRequestConnection *connection,
                                              id result,
                                              NSError *error
                                              ) {
     
     
    if (result && !error) {
        NSLog(@"good");

        if ([[result objectForKey:@"data"] count] > 0)  {
     
     
            for (id data : [result objectForKey:@"data"]) {
                int score = [[data objectForKey:@"score"] intValue];
                NSLog(@"score");
    
                id user = [data objectForKey:@"user"];
                NSString* name = [user objectForKey:@"name"];
     //NSString* userId = [user objectForKey:@"id"];
     
     //                             iOSBridge::Callbacks::FacebookScore* sc = new iOSBridge::Callbacks::FacebookScore();
     //sc->name = [name cStringUsingEncoding:[NSString defaultCStringEncoding]];
     //sc->score = score;
     
     
                NSLog(@"User: %@ - score: %i", name, score);
            }
     
     
        }
        std::vector<GKScoreCpp> scores;
       // _gkhDelegate->onScoresReceived(scores);
     
     } else {
                                        std::vector<GKScoreCpp> scores;
        //tmpDelegate->onScoresReceived(scores);
         //[ScoreRequestDelegate
         tmpDelegate->onScoresReceived(scores);
     }
     
     }];
}

#pragma mark Delegate

-(void)setDelegate:(FBHWrapperCpp*)gkhDelegate{
    
    _gkhDelegate = gkhDelegate;
    
}


#pragma mark C++/Objective-C type converters



@end
