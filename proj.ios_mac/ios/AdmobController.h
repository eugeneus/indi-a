

#import <UIKit/UIKit.h>

extern NSString * const BannerViewActionWillBegin;
extern NSString * const BannerViewActionDidFinish;

@interface AdmobController : UIViewController

- (instancetype)initWithContentViewController:(UIViewController *)contentController withSize:(CGSize)size;

@end
