
#include "FBHWrapperCpp.h"
#import "FacebookHelper.h"

FBHWrapperCpp::FBHWrapperCpp(){
    
    [FacebookHelper sharedHelper];
    
}

void FBHWrapperCpp::retrieveTopTenAllTimeGlobalScores(std::string catagory){
    
    FacebookHelper *helper = [FacebookHelper sharedHelper];
    [helper retrieveTopTenAllTimeGlobalScoresForCatagory:[NSString stringWithUTF8String:catagory.c_str()]];
    
}

#pragma mark Delegate

void FBHWrapperCpp::setDelegate(FBHDelegate* delegate){
    
    FacebookHelper *helper = [FacebookHelper sharedHelper];
    [helper setDelegate:delegate];
    
}