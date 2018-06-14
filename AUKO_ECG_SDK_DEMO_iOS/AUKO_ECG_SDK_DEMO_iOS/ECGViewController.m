//
//  ECGViewController.m
//  AUKO_ECG_SDK_DEMO_iOS
//
//  Created by ecg on 2018/6/14.
//  Copyright © 2018年 Auko. All rights reserved.
//

#import <ECG_SDK/ECG_SDK.h>
#import <ECG_Draw_SDK/ECG_Draw_SDK.h>

//#import "ECGBackground.h"
#import "ECGViewController.h"

@interface ECGViewController ()

// 定时器
@property (nonatomic,strong) dispatch_source_t drawECGTimer;
// UI控件
@property (nonatomic,strong) ECGBackground     *backgroundView;
@property (nonatomic,strong) ECGDraw           *ecgDrawView;
@property (nonatomic,strong) UILabel           *heartBeatLabel;
@property (nonatomic,strong) UILabel           *heartBeatTimeLabel;
@property (nonatomic,strong) UILabel           *distanceLabel;
@property (nonatomic,strong) NSDateFormatter   *dateFormatter;

@end

@implementation ECGViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setUpECGDrawView];
    
    //    [[NSNotificationCenter defaultCenter] addObserver:self
    //                                             selector:@selector(receivedNotification:)
    //                                                 name:kReceivedECGOneSecPacketNotification
    //                                               object:nil];
}

- (void)receivedNotification:(NSNotification *)notify {
    OneSecondPacket *packet = notify.userInfo[kOneSecPacketKey];
    NSLog(@"%@",[self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:packet.date/1000]]);
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.ecgDrawView start];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    dispatch_source_cancel(_drawECGTimer);
    [self.ecgDrawView stop];
    [JSBluetoothManager.sharedCentralBLEManager js_disconnect];
}

- (void)setUpECGDrawView {
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    CGFloat topMargin    = 110;
    CGFloat bottomMargin = 20;
    CGRect backViewRect  = CGRectMake(0, topMargin, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height - topMargin - bottomMargin);
    CGRect ecgDrawRect   = CGRectMake(0, topMargin + 18, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height - topMargin - bottomMargin - 18);
    
    // View
    self.backgroundView                   = [[ECGBackground alloc] initWithFrame:backViewRect withType:1];
    self.backgroundView.backgroundColor   = [UIColor whiteColor];
    self.ecgDrawView                      = [[ECGDraw alloc] initWithFrame:ecgDrawRect];
    self.ecgDrawView.backgroundColor      = [UIColor colorWithRed:1 green:1 blue:1 alpha:0.01];
    // Label
    self.heartBeatLabel                   = [[UILabel alloc] initWithFrame:CGRectMake(0, 70, self.ecgDrawView.bounds.size.width * 0.3, 40)];
    self.heartBeatLabel.font              = [UIFont boldSystemFontOfSize:40];
    self.heartBeatLabel.textAlignment     = NSTextAlignmentCenter;
    self.heartBeatLabel.textColor         = [UIColor blackColor];
    self.heartBeatLabel.text              = @"000";
    self.heartBeatTimeLabel               = [[UILabel alloc] initWithFrame:CGRectMake(0 + self.heartBeatLabel.bounds.size.width, 70, self.ecgDrawView.bounds.size.width * 0.4, 40)];
    self.heartBeatTimeLabel.font          = [UIFont systemFontOfSize:13];
    self.heartBeatTimeLabel.textColor     = [UIColor blackColor];
    self.heartBeatTimeLabel.text          = @"- - -";
    self.heartBeatTimeLabel.textAlignment = NSTextAlignmentCenter;
    self.distanceLabel                    = [[UILabel alloc] initWithFrame:CGRectMake(self.ecgDrawView.bounds.size.width * 0.7, 70, self.ecgDrawView.bounds.size.width * 0.3, 40)];
    self.distanceLabel.font               = [UIFont systemFontOfSize:13];
    self.distanceLabel.textColor          = [UIColor blackColor];
    
    
    [self.view addSubview:self.heartBeatLabel];
    [self.view addSubview:self.heartBeatTimeLabel];
    [self.view addSubview:self.distanceLabel];
    [self.view addSubview:self.backgroundView];
    [self.view addSubview:self.ecgDrawView];
    
    _drawECGTimer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(0, 0));
    dispatch_source_set_timer(_drawECGTimer, DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC, 0.1 * NSEC_PER_SEC);
    dispatch_source_set_event_handler(_drawECGTimer, ^{
        CFAbsoluteTime start             = CFAbsoluteTimeGetCurrent();
        __block CFAbsoluteTime end       = 0;
        OneSecondPacket *oneSecondPacket = [[JSECGPacketCarrier sharedECGPacketCarrierManager] getRealTimeEcgdata];
        if (oneSecondPacket) {
            //NSLog(@" ****** 实时心电数据时间:  %@  ****** ",[NSDate dateWithTimeIntervalSince1970:oneSecondPacket.date/1000]);
            dispatch_sync(dispatch_get_main_queue(), ^{
                // 1.心电图
                [self.ecgDrawView updataEcgdatas:oneSecondPacket andType:0];
                // 2.心率
                int rateNum = oneSecondPacket.rate;
                NSString *rateStr = @"000";
                if ( rateNum < 10 ) {
                    rateStr = [NSString stringWithFormat:@"00%d",rateNum];
                } else if (rateNum < 100 && rateNum >= 10){
                    rateStr = [NSString stringWithFormat:@"0%d",rateNum];
                } else if (rateNum < 1000){
                    rateStr = [NSString stringWithFormat:@"%d",rateNum];
                }
                self.heartBeatLabel.text     = rateStr;
                // 3.时间
                self.heartBeatTimeLabel.text = [self.dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:oneSecondPacket.date/1000]];
                // 4. 距离
                float distance               = JSBluetoothManager.sharedCentralBLEManager.peripheralConnected.distance.floatValue;
                self.distanceLabel.text      = [NSString stringWithFormat:@"距离:%.2f米",distance];
            });
        }
        end = CFAbsoluteTimeGetCurrent();
        if (end > 0) {
            CFAbsoluteTime offset = end - start;
            sleep(1 - offset);
        } else {
            // NSLog(@"取空");
        }
    });
    dispatch_resume(_drawECGTimer);
}

#pragma mark - lazy loading
- (NSDateFormatter *)dateFormatter {
    if (!_dateFormatter) {
        _dateFormatter            = [[NSDateFormatter alloc] init];
        _dateFormatter.dateFormat = @"HH:mm:ss";
    }
    return _dateFormatter;
}

@end
