

#import <UIKit/UIKit.h>

@class OneSecondPacket;

@interface ECGDraw : UIView

- (void)updataEcgdatas:(OneSecondPacket *)oneSecPacket andType:(int)type;

- (void)start;
- (void)stop;


@end
