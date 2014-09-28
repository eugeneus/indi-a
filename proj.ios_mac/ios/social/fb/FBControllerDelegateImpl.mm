
#import "FBControllerDelegateImpl.h"
#import "ScoreUserEntity.h"
#import "UserScoreResult.h"

USING_NS_CC;

@implementation FBControllerDelegateImpl

- (void)onScoresReceived:(NSMutableDictionary *) res {
    NSLog(@"sdfsdfsd");
    
    cocos2d::Vector<ScoreUserEntity *> scores;
    for (id data : res) {
        int score = [[data objectForKey:@"score"] intValue];
        id user = [data objectForKey:@"user"];
        NSString* name = [user objectForKey:@"name"];
        NSString* userId = [user objectForKey:@"id"];
        
        //                             iOSBridge::Callbacks::FacebookScore* sc = new iOSBridge::Callbacks::FacebookScore();
        //sc->name = [name cStringUsingEncoding:[NSString defaultCStringEncoding]];
        //sc->score = score;
        
        NSLog(@"User: %@ - score: %i", name, score);
        
        ScoreUserEntity *userScore = ScoreUserEntity::create(*new std::string([name UTF8String]), *new std::string([userId UTF8String]), score);
        scores.pushBack(userScore);
        
    }
    UserScoreResult *result = UserScoreResult::create();
    result->addData(scores);
    
    NotificationCenter::getInstance()->postNotification("score_complete", result);
}

- (void)onError {
    NSLog(@"sdfsdfsd");
    NotificationCenter::getInstance()->postNotification("score_error");
}

@end
