
#include "ScoreUtility.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "GameCenterManager.h"
#import "GameCenterDelegate.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniHelper.h"
#endif

USING_NS_CC;

void ScoreUtility::showLeaderboard() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [[[GameCenterManager instance] delegate] showLeaderboard];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "com/droidcorp/utils/ScoreUtility"
                                       , "showLeaderboard"
                                       , "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#endif
}

void ScoreUtility::submitScore() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [[[GameCenterManager instance] delegate] reportByScore];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "com/droidcorp/utils/ScoreUtility"
                                       , "submitScore"
                                       , "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#endif
}

bool ScoreUtility::isLeaderboardAvailable() {
    bool isLeaderboardAvailable = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isLeaderboardAvailable = [GameCenterManager isGameCenterAvailable];
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "com/droidcorp/utils/ScoreUtility"
                                       , "isLeaderboardAvailable"
                                       , "()Z")) {
        isLeaderboardAvailable = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
    }
#endif
    return isLeaderboardAvailable;
}